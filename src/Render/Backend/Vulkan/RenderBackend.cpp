#include "RenderBackend.h"
#include "Infrastructure/Instance.h"
#include "Infrastructure/Functions.h"
#include "Infrastructure/KHR/Surface.h"
#include "Infrastructure/PhysicalDevice.h"
#include "Infrastructure/Device.h"
#include "Infrastructure/MemoryAllocator.h"
#include "Infrastructure/ThreadQueue.h"
#include "Infrastructure/KHR/SwapChain.h"
#include "Window/Window.h"

namespace PlayGround::Vulkan {

    RenderBackend::RenderBackend(Window* window)
        : RenderFrontend()
    {
        m_Context = CreateSP<Context>();

        m_Context->Registry<Instance>();
        m_Context->Registry<Surface>();
        m_Context->Registry<PhysicalDevice>();
        m_Context->Registry<Device>();
        m_Context->Registry<MemoryAllocator>();
        m_Context->Registry<SwapChain>(static_cast<GLFWwindow*>(window->NativeWindow()));
    }

    RenderBackend::~RenderBackend()
    {

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