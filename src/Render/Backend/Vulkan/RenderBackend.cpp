#include "RenderBackend.h"
#include "Infrastructure/Instance.h"
#include "Infrastructure/Functions.h"
#include "Infrastructure/Surface.h"
#include "Infrastructure/PhysicalDevice.h"
#include "Infrastructure/Device.h"
#include "Infrastructure/MemoryAllocator.h"
#include "Infrastructure/ThreadQueue.h"
#include "Infrastructure/SwapChain.h"
#include "Infrastructure/Semaphore.h"
#include "Infrastructure/Fence.h"
#include "Infrastructure/DebugUtilsObject.h"
#include "Infrastructure/CommandPool.h"
#include "Infrastructure/CommandBuffer.h"
#include "Infrastructure/Queue.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "World/Component/ClockComponent.h"

namespace PlayGround::Vulkan {

    RenderBackend::RenderBackend(Window* window)
        : RenderFrontend()
		, m_Window(window)
    {
        m_Context = CreateSP<Context>();

        m_Context->Registry<IInstance>();
        m_Context->Registry<IDebugUtilsObject>();
        m_Context->Registry<ISurface>();
        m_Context->Registry<IPhysicalDevice>();
        m_Context->Registry<IDevice>();

        m_Context->Registry<IMemoryAllocator>();
        m_Context->Registry<ISwapChain>(static_cast<GLFWwindow*>(window->NativeWindow()), MaxFrameInFlight);

        m_Context->Registry<IGraphicImageSemaphore>(MaxFrameInFlight);
        m_Context->Registry<IGraphicQueueSemaphore>(MaxFrameInFlight);
        m_Context->Registry<IGraphicFence>(MaxFrameInFlight);

        m_Context->Registry<IComputeQueueSemaphore>(MaxFrameInFlight);
        m_Context->Registry<IComputeFence>(MaxFrameInFlight);

        m_Context->Registry<IGraphicCommandPool>(m_Context->Get<IPhysicalDevice>()->GetQueueFamilies().graphic.value());
        m_Context->Registry<IGraphicCommandBuffer>(m_Context->Get<IGraphicCommandPool>()->Handle(), VK_COMMAND_BUFFER_LEVEL_PRIMARY, MaxFrameInFlight);

        m_Context->Registry<IComputeCommandPool>(m_Context->Get<IPhysicalDevice>()->GetQueueFamilies().compute.value());
        m_Context->Registry<IComputeCommandBuffer>(m_Context->Get<IComputeCommandPool>()->Handle(), VK_COMMAND_BUFFER_LEVEL_PRIMARY, MaxFrameInFlight);
    }

    RenderBackend::~RenderBackend()
    {
        m_Context->UnRegistry<IComputeCommandBuffer>();
        m_Context->UnRegistry<IComputeCommandPool>();
        
        m_Context->UnRegistry<IGraphicCommandBuffer>();
        m_Context->UnRegistry<IGraphicCommandPool>();
        
        m_Context->UnRegistry<IComputeFence>();
        m_Context->UnRegistry<IComputeQueueSemaphore>();

        m_Context->UnRegistry<IGraphicFence>();
        m_Context->UnRegistry<IGraphicQueueSemaphore>();
        m_Context->UnRegistry<IGraphicImageSemaphore>();

        m_Context->UnRegistry<ISwapChain>();
        m_Context->UnRegistry<IMemoryAllocator>();

        m_Context->UnRegistry<IComputeThreadQueue>();
        m_Context->UnRegistry<IGraphicThreadQueue>();
        
        m_Context->UnRegistry<ITransferQueue>();
        m_Context->UnRegistry<IComputeQueue>();
        m_Context->UnRegistry<IPresentQueue>();
        m_Context->UnRegistry<IGraphicQueue>();
        
        m_Context->UnRegistry<IDevice>();
        m_Context->UnRegistry<IPhysicalDevice>();
        m_Context->UnRegistry<ISurface>();
        m_Context->UnRegistry<IDebugUtilsObject>();
        m_Context->UnRegistry<IInstance>();
        m_Context->UnRegistry<IFunctions>();
    }

	Context& RenderBackend::GetContext()
	{
		return *m_Context;
	}

    void RenderBackend::BeginFrame(Scene* scene)
    {
		auto& clock = scene->GetComponent<ClockComponent>(scene->GetRoot()).GetClock();

		{
			m_Context->Get<IComputeFence>()->Wait(clock.m_FrameIndex);

			m_Context->Get<IGraphicFence>()->Wait(clock.m_FrameIndex);
		}

		{
			

			if (!m_Context->Get<ISwapChain>()->GetNextImage(m_Context->Get<IGraphicImageSemaphore>()->Handle(clock.m_FrameIndex), clock.m_ImageIndex))
			{
				RecreateSwapChain();
			}
		}

		{
			VkCommandBufferBeginInfo     beginInfo{};
			beginInfo.sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags            = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
			beginInfo.pInheritanceInfo = nullptr;

            m_Context->Get<IComputeCommandBuffer>()->Begin(beginInfo, clock.m_FrameIndex);

            beginInfo.flags |= VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
            m_Context->Get<IGraphicCommandBuffer>()->Begin(beginInfo, clock.m_FrameIndex);
		}
    }

    void RenderBackend::EndFrame(Scene* scene)
    {
		auto& clock = scene->GetComponent<ClockComponent>(scene->GetRoot()).GetClock();

		{
			m_Context->Get<IComputeCommandBuffer>()->End(clock.m_FrameIndex);

			m_Context->Get<IGraphicCommandBuffer>()->End(clock.m_FrameIndex);
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(m_Context->Get<IComputeQueue>()->Handle(), "MainComputeQueue")

			VkSemaphore waitSemphores[]          = { m_Context->Get<IGraphicImageSemaphore>()->Handle(clock.m_FrameIndex) };
			VkSemaphore signalSemaphores[]       = { m_Context->Get<IComputeQueueSemaphore>()->Handle(clock.m_FrameIndex) };
			VkPipelineStageFlags waitStages[]    = { VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT };

			VkSubmitInfo                           submitInfo{};
			submitInfo.sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.waitSemaphoreCount        = 1;
			submitInfo.pWaitSemaphores           = waitSemphores;
			submitInfo.pWaitDstStageMask         = waitStages;
			submitInfo.commandBufferCount        = 1;
			submitInfo.pCommandBuffers           = &m_Context->Get<IComputeCommandBuffer>()->Handle(clock.m_FrameIndex);
			submitInfo.signalSemaphoreCount      = 1;
			submitInfo.pSignalSemaphores         = signalSemaphores;

			m_Context->Get<IComputeQueue>()->Submit(submitInfo, m_Context->Get<IComputeFence>()->Handle(clock.m_FrameIndex));

			DEBUGUTILS_ENDQUEUELABEL(m_Context->Get<IComputeQueue>()->Handle())
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(m_Context->Get<IGraphicQueue>()->Handle(), "MainGraphicQueue")

			VkSemaphore waitSemphores[]          = { m_Context->Get<IComputeQueueSemaphore>()->Handle(clock.m_FrameIndex) };
			VkSemaphore signalSemaphores[]       = { m_Context->Get<IGraphicQueueSemaphore>()->Handle(clock.m_FrameIndex) };
			VkPipelineStageFlags waitStages[]    = { VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

			VkSubmitInfo                           submitInfo{};
			submitInfo.sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.waitSemaphoreCount        = 1;
			submitInfo.pWaitSemaphores           = waitSemphores;
			submitInfo.pWaitDstStageMask         = waitStages;
			submitInfo.commandBufferCount        = 1;
			submitInfo.pCommandBuffers           = &m_Context->Get<IGraphicCommandBuffer>()->Handle(clock.m_FrameIndex);
			submitInfo.signalSemaphoreCount      = 1;
			submitInfo.pSignalSemaphores         = signalSemaphores;

			m_Context->Get<IGraphicQueue>()->Submit(submitInfo, m_Context->Get<IGraphicFence>()->Handle(clock.m_FrameIndex));

			DEBUGUTILS_ENDQUEUELABEL(m_Context->Get<IGraphicQueue>()->Handle())
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(m_Context->Get<IPresentQueue>()->Handle(), "PresentQueue")

			VkPresentInfoKHR                       presentInfo{};
			presentInfo.sType                    = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
			presentInfo.waitSemaphoreCount       = 1;
			presentInfo.pWaitSemaphores          = &m_Context->Get<IGraphicQueueSemaphore>()->Handle(clock.m_FrameIndex);
			presentInfo.swapchainCount           = 1;
			presentInfo.pImageIndices            = &clock.m_ImageIndex;
			presentInfo.pResults                 = nullptr;

			if (!m_Context->Get<ISwapChain>()->Present(presentInfo))
			{
				RecreateSwapChain();
			}

			DEBUGUTILS_ENDQUEUELABEL(m_Context->Get<IPresentQueue>()->Handle())
		}
    }

    void RenderBackend::RenderFrame(Scene* scene)
    {

    }

	void RenderBackend::RecreateSwapChain()
	{
		auto glfwWindow = static_cast<GLFWwindow*>(m_Window->NativeWindow());

		GetContext().Get<IGraphicQueue>()->Wait();

		RenderFrontend::RecreateSwapChain();

		GetContext().Get<ISwapChain>()->ReCreate(glfwWindow, MaxFrameInFlight);
	}
}