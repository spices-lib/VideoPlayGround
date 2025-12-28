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
#include "Infrastructure/DescriptorPool.h"
#include "Infrastructure/Queue.h"
#include "Window/Window.h"
#include "World/Scene/Scene.h"
#include "World/Component/ClockComponent.h"
#include "Render/Backend/Vulkan/RHIResource/VideoSession.h"
#include "Render/Frontend/Pass/SlatePass.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <backends/imgui_impl_vulkan.h>
#include <backends/imgui_impl_glfw.h>
#include "Render/Frontend/RHI/RenderPass.h"
#include "Render/Backend/Vulkan/RHIResource/RenderPass.h"
#include "Render/Backend/Vulkan/RHIResource/Descriptor.h"
#include "Render/Backend/Vulkan/RHIResource/Pipeline.h"
#include "Render/Backend/Vulkan/RHIResource/Shader.h"
#include "Render/Backend/Vulkan/RHIResource/RenderTarget.h"
#include "Render/Backend/Vulkan/RHIResource/VertexBuffer.h"
#include "Render/Backend/Vulkan/RHIResource/IndexBuffer.h"
#include "Render/Backend/Vulkan/RHIResource/CmdList.h"

namespace PlayGround::Vulkan {

    RenderBackend::RenderBackend(Window* window)
        : RenderFrontend()
		, m_Window(window)
    {}

	void RenderBackend::OnInitialize()
	{
		m_Context = CreateSP<Context>();

		m_Context->Registry<IInstance>();
		m_Context->Registry<IDebugUtilsObject>();
		m_Context->Registry<ISurface>();
		m_Context->Registry<IPhysicalDevice>();
		m_Context->Registry<IDevice>();

		m_Context->Registry<IMemoryAllocator>();
		m_Context->Registry<ISwapChain>(static_cast<GLFWwindow*>(m_Window->NativeWindow()), MaxFrameInFlight);

		m_Context->Registry<IGraphicImageSemaphore>(MaxFrameInFlight);
		m_Context->Registry<IGraphicQueueSemaphore>(MaxFrameInFlight);
		m_Context->Registry<IGraphicFence>(MaxFrameInFlight);

		m_Context->Get<IGraphicImageSemaphore>()->SetName("GraphicImageSemaphore");
		m_Context->Get<IGraphicQueueSemaphore>()->SetName("GraphicQueueSemaphore");
		m_Context->Get<IGraphicFence>()->SetName("GraphicFence");

		m_Context->Registry<IComputeQueueSemaphore>(MaxFrameInFlight);
		m_Context->Registry<IComputeFence>(MaxFrameInFlight);

		m_Context->Get<IComputeQueueSemaphore>()->SetName("ComputeQueueSemaphore");
		m_Context->Get<IComputeFence>()->SetName("ComputeFence");

		m_Context->Registry<IVideoEncodeQueueSemaphore>(MaxFrameInFlight);
		m_Context->Registry<IVideoEncodeFence>(MaxFrameInFlight);

		m_Context->Get<IVideoEncodeQueueSemaphore>()->SetName("VideoEncodeQueueSemaphore");
		m_Context->Get<IVideoEncodeFence>()->SetName("VideoEncodeFence");

		m_Context->Registry<IGraphicCommandPool>(m_Context->Get<IPhysicalDevice>()->GetQueueFamilies().graphic.value());
		m_Context->Registry<IGraphicCommandBuffer>(m_Context->Get<IGraphicCommandPool>()->Handle(), VK_COMMAND_BUFFER_LEVEL_PRIMARY, MaxFrameInFlight);

		m_Context->Get<IGraphicCommandPool>()->SetName("GraphicCommandPool");
		m_Context->Get<IGraphicCommandBuffer>()->SetName("GraphicCommandBuffer");

		m_Context->Registry<IComputeCommandPool>(m_Context->Get<IPhysicalDevice>()->GetQueueFamilies().compute.value());
		m_Context->Registry<IComputeCommandBuffer>(m_Context->Get<IComputeCommandPool>()->Handle(), VK_COMMAND_BUFFER_LEVEL_PRIMARY, MaxFrameInFlight);

		m_Context->Get<IComputeCommandPool>()->SetName("ComputeCommandPool");
		m_Context->Get<IComputeCommandBuffer>()->SetName("ComputeCommandBuffer");

		m_Context->Registry<IVideoEncodeCommandPool>(m_Context->Get<IPhysicalDevice>()->GetQueueFamilies().videoEncode.value());
		m_Context->Registry<IVideoEncodeCommandBuffer>(m_Context->Get<IVideoEncodeCommandPool>()->Handle(), VK_COMMAND_BUFFER_LEVEL_PRIMARY, MaxFrameInFlight);

		m_Context->Get<IVideoEncodeCommandPool>()->SetName("VideoEncodeCommandPool");
		m_Context->Get<IVideoEncodeCommandBuffer>()->SetName("VideoEncodeCommandBuffer");

		m_Context->Registry<IDescriptorPool>();

		m_Context->Get<IDescriptorPool>()->SetName("DescriptorPool");

		RenderFrontend::OnInitialize();
	}

	void RenderBackend::OnShutDown()
	{
		RenderFrontend::OnShutDown();

		m_Context->UnRegistry<IDescriptorPool>();

		m_Context->UnRegistry<IVideoEncodeCommandBuffer>();
		m_Context->UnRegistry<IVideoEncodeCommandPool>();

		m_Context->UnRegistry<IComputeCommandBuffer>();
		m_Context->UnRegistry<IComputeCommandPool>();

		m_Context->UnRegistry<IGraphicCommandBuffer>();
		m_Context->UnRegistry<IGraphicCommandPool>();

		m_Context->UnRegistry<IVideoEncodeFence>();
		m_Context->UnRegistry<IVideoEncodeQueueSemaphore>();

		m_Context->UnRegistry<IComputeFence>();
		m_Context->UnRegistry<IComputeQueueSemaphore>();

		m_Context->UnRegistry<IGraphicFence>();
		m_Context->UnRegistry<IGraphicQueueSemaphore>();
		m_Context->UnRegistry<IGraphicImageSemaphore>();

		m_Context->UnRegistry<ISwapChain>();
		m_Context->UnRegistry<IMemoryAllocator>();

		m_Context->UnRegistry<IComputeThreadQueue>();
		m_Context->UnRegistry<IGraphicThreadQueue>();

		m_Context->UnRegistry<IVideoEncodeQueue>();
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

	Context& RenderBackend::GetContext() const
	{
		return *m_Context;
	}

    void RenderBackend::BeginFrame(Scene* scene)
    {
		auto& clock = scene->GetComponent<ClockComponent>(scene->GetRoot()).GetClock();

		{
			m_Context->Get<IVideoEncodeFence>()->Wait(clock.m_FrameIndex);

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
			VkCommandBufferBeginInfo               beginInfo{};
			beginInfo.sType                      = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			beginInfo.flags                      = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
			beginInfo.pInheritanceInfo           = nullptr;

			m_Context->Get<IVideoEncodeCommandBuffer>()->Begin(beginInfo, clock.m_FrameIndex);

            m_Context->Get<IComputeCommandBuffer>()->Begin(beginInfo, clock.m_FrameIndex);

            beginInfo.flags |= VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT;
            m_Context->Get<IGraphicCommandBuffer>()->Begin(beginInfo, clock.m_FrameIndex);
		}
    }

    void RenderBackend::EndFrame(Scene* scene)
    {
		auto& clock = scene->GetComponent<ClockComponent>(scene->GetRoot()).GetClock();

		{
			m_Context->Get<IVideoEncodeCommandBuffer>()->End(clock.m_FrameIndex);

			m_Context->Get<IComputeCommandBuffer>()->End(clock.m_FrameIndex);

			m_Context->Get<IGraphicCommandBuffer>()->End(clock.m_FrameIndex);
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(m_Context->Get<IVideoEncodeQueue>()->Handle(), "MainVideoEncodeQueue")

			VkSemaphore waitSemphores[]          = { m_Context->Get<IGraphicImageSemaphore>()->Handle(clock.m_FrameIndex) };
			VkSemaphore signalSemaphores[]       = { m_Context->Get<IVideoEncodeQueueSemaphore>()->Handle(clock.m_FrameIndex) };
			VkPipelineStageFlags waitStages[]    = { VK_PIPELINE_STAGE_ALL_COMMANDS_BIT };

			VkSubmitInfo                           submitInfo{};
			submitInfo.sType                     = VK_STRUCTURE_TYPE_SUBMIT_INFO;
			submitInfo.waitSemaphoreCount        = 1;
			submitInfo.pWaitSemaphores           = waitSemphores;
			submitInfo.pWaitDstStageMask         = waitStages;
			submitInfo.commandBufferCount        = 1;
			submitInfo.pCommandBuffers           = &m_Context->Get<IVideoEncodeCommandBuffer>()->Handle(clock.m_FrameIndex);
			submitInfo.signalSemaphoreCount      = 1;
			submitInfo.pSignalSemaphores         = signalSemaphores;

			m_Context->Get<IVideoEncodeQueue>()->Submit(submitInfo, m_Context->Get<IVideoEncodeFence>()->Handle(clock.m_FrameIndex));

			DEBUGUTILS_ENDQUEUELABEL(m_Context->Get<IVideoEncodeQueue>()->Handle())
		}

		{
			DEBUGUTILS_BEGINQUEUELABEL(m_Context->Get<IComputeQueue>()->Handle(), "MainComputeQueue")

			VkSemaphore waitSemphores[]          = { m_Context->Get<IVideoEncodeQueueSemaphore>()->Handle(clock.m_FrameIndex) };
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

  //  void RenderBackend::RenderFrame(Scene* scene)
  //  {
		///*auto& clock = scene->GetComponent<ClockComponent>(scene->GetRoot()).GetClock();

		//VideoSession session(*m_Context);

		//session.CreateVideoSession();

		//session.CreateVideoSessionParameters();

		//session.UpdateVideoSessionParameters();

		//VkVideoBeginCodingInfoKHR                    encodeBeginInfo{};
		//encodeBeginInfo.sType                      = VK_STRUCTURE_TYPE_VIDEO_BEGIN_CODING_INFO_KHR;
		//encodeBeginInfo.videoSession               = session.Handle();
		//encodeBeginInfo.videoSessionParameters     = session.Parameters();
		//encodeBeginInfo.referenceSlotCount         = 0;
		//encodeBeginInfo.pReferenceSlots            = 0;
		//encodeBeginInfo.pNext                      = nullptr;

  //      GetContext().Get<IFunctions>()->vkCmdBeginVideoCodingKHR(GetContext().Get<IVideoEncodeCommandBuffer>()->Handle(clock.m_FrameIndex), &encodeBeginInfo);

		//StdVideoDecodeH265PictureInfo stdPictureInfo = {};

		//uint32_t offset = 0;

		//VkVideoDecodeH265PictureInfoKHR              decodeH265PictureInfo{};
		//decodeH265PictureInfo.sType                = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PICTURE_INFO_KHR;
		//decodeH265PictureInfo.pStdPictureInfo      = &stdPictureInfo;
		//decodeH265PictureInfo.sliceSegmentCount    = 1;
		//decodeH265PictureInfo.pSliceSegmentOffsets = &offset;
		//decodeH265PictureInfo.pNext                = nullptr;

		//VkVideoDecodeInfoKHR                         decodeInfo{};
		//decodeInfo.sType                           = VK_STRUCTURE_TYPE_VIDEO_DECODE_INFO_KHR;
		//decodeInfo.pSetupReferenceSlot             = nullptr;
		//decodeInfo.referenceSlotCount              = 0;
		//decodeInfo.pReferenceSlots                 = nullptr;
		//decodeInfo.srcBuffer                       = nullptr;
		//decodeInfo.dstPictureResource              = {};
		//decodeInfo.pNext                           = &decodeH265PictureInfo;

		//GetContext().Get<IFunctions>()->vkCmdDecodeVideoKHR(GetContext().Get<IVideoEncodeCommandBuffer>()->Handle(clock.m_FrameIndex), &decodeInfo);

		//VkVideoEndCodingInfoKHR                      decodeEndInfo{};
		//decodeEndInfo.sType                        = VK_STRUCTURE_TYPE_VIDEO_END_CODING_INFO_KHR;

		//GetContext().Get<IFunctions>()->vkCmdEndVideoCodingKHR(GetContext().Get<IVideoEncodeCommandBuffer>()->Handle(clock.m_FrameIndex), &decodeEndInfo);*/
  //  }

	void RenderBackend::Wait()
	{
		m_Context->Get<IDevice>()->Wait();
	}

	void RenderBackend::InitSlateModule()
	{
		auto pass = std::dynamic_pointer_cast<Render::SlatePass>(m_RenderPasses.back());

		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();

		io.IniFilename  = "Layout.ini";
		io.LogFilename  = nullptr;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui_ImplGlfw_InitForVulkan(static_cast<GLFWwindow*>(m_Window->NativeWindow()), true);

		ImGui_ImplVulkan_InitInfo             init_info{};
		init_info.Instance                  = m_Context->Get<IInstance>()->Handle();
		init_info.PhysicalDevice            = m_Context->Get<IPhysicalDevice>()->Handle();
		init_info.Device                    = m_Context->Get<IDevice>()->Handle();
		init_info.QueueFamily               = m_Context->Get<IPhysicalDevice>()->GetQueueFamilies().graphic.value();
		init_info.Queue                     = m_Context->Get<IGraphicQueue>()->Handle();
		init_info.PipelineCache             = VK_NULL_HANDLE;
		init_info.DescriptorPool            = m_Context->Get<IDescriptorPool>()->Handle();
		init_info.RenderPass                = pass->GetRenderPass()->GetRHIImpl<RenderPass>()->Handle();
		init_info.Subpass                   = 0;
		init_info.MinImageCount             = MaxFrameInFlight;
		init_info.ImageCount                = MaxFrameInFlight;
		init_info.MSAASamples               = VK_SAMPLE_COUNT_1_BIT;
		init_info.Allocator                 = VK_NULL_HANDLE;
		init_info.CheckVkResultFn           = [](VkResult result) { VK_CHECK(result); };

		ImGui_ImplVulkan_Init(&init_info);

		ImGui_ImplVulkan_CreateFontsTexture();
	}

	std::any RenderBackend::CreateRHI(RHI::ERHI e)
	{
		switch(e)
		{
			case RHI::ERHI::RenderPass:   return std::dynamic_pointer_cast<RHI::RenderPass::Impl>  (CreateSP<RenderPass>  (*m_Context));
			case RHI::ERHI::Descriptor:   return std::dynamic_pointer_cast<RHI::Descriptor::Impl>  (CreateSP<Descriptor>  (*m_Context));
			case RHI::ERHI::Pipeline:     return std::dynamic_pointer_cast<RHI::Pipeline::Impl>    (CreateSP<Pipeline>    (*m_Context));
			case RHI::ERHI::Shader:       return std::dynamic_pointer_cast<RHI::Shader::Impl>      (CreateSP<Shader>      (*m_Context));
			case RHI::ERHI::RenderTarget: return std::dynamic_pointer_cast<RHI::RenderTarget::Impl>(CreateSP<RenderTarget>(*m_Context));
			case RHI::ERHI::VertexBuffer: return std::dynamic_pointer_cast<RHI::VertexBuffer::Impl>(CreateSP<VertexBuffer>(*m_Context));
			case RHI::ERHI::IndexBuffer:  return std::dynamic_pointer_cast<RHI::IndexBuffer::Impl> (CreateSP<IndexBuffer> (*m_Context));
			case RHI::ERHI::CmdList:      return std::dynamic_pointer_cast<RHI::CmdList::Impl>     (CreateSP<CmdList>     (*m_Context));
			default: return nullptr;
		}
	}

	void RenderBackend::RecreateSwapChain()
	{
		auto glfwWindow = static_cast<GLFWwindow*>(m_Window->NativeWindow());

		GetContext().Get<IGraphicQueue>()->Wait();

		GetContext().Get<ISwapChain>()->ReCreate(glfwWindow, MaxFrameInFlight);

		RenderFrontend::RecreateSwapChain();
	}
}
