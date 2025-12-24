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

namespace PlayGround::Vulkan {

    RenderBackend::RenderBackend(Window* window)
        : RenderFrontend()
    {
        m_Context = CreateSP<Context>();

        m_Context->Registry<IInstance>();
        m_Context->Registry<IDebugUtilsObject>();
        m_Context->Registry<ISurface>();
        m_Context->Registry<IPhysicalDevice>();
        m_Context->Registry<IDevice>();

        m_Context->Registry<IMemoryAllocator>();
        m_Context->Registry<ISwapChain>(static_cast<GLFWwindow*>(window->NativeWindow()));

        m_Context->Registry<IGraphicImageSemaphore>();
        m_Context->Registry<IGraphicQueueSemaphore>();
        m_Context->Registry<IGraphicFence>();

        m_Context->Registry<IComputeQueueSemaphore>();
        m_Context->Registry<IComputeFence>();

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

    void RenderBackend::BeginFrame()
    {

    }

    void RenderBackend::EndFrame()
    {

    }

    void RenderBackend::RenderFrame()
    {

    }
}