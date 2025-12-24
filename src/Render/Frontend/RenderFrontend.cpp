#include "RenderFrontend.h"
#include "Render/Backend/Vulkan/RenderBackend.h"
#include "Window/Window.h"
#include "Core/Event/WindowEvent.h"
#include <GLFW/glfw3.h>

namespace PlayGround {

    SP<RenderFrontend> RenderFrontend::Create()
    {
        return CreateSP<Vulkan::RenderBackend>(&Window::Instance());
    }

    void RenderFrontend::RecreateSwapChain()
    {
        auto glfwWindow = static_cast<GLFWwindow*>(Window::Instance().NativeWindow());

        int width = 0, height = 0;
        glfwGetFramebufferSize(glfwWindow, &width, &height);

        while (width == 0 || height == 0)
        {
            glfwGetFramebufferSize(glfwWindow, &width, &height);
            glfwWaitEvents();
        }

        WindowResizeOverEvent event(width, height);

        Event::GetEventCallbackFn()(event);
    }

}