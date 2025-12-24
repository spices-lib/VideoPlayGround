#include "Surface.h"
#include "Window/Window.h"

#include <GLFW/glfw3.h>

namespace PlayGround::Vulkan {

    Surface::Surface(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        Create();
    }

    void Surface::Create()
    {
        const auto instance = GetContext().Get<IInstance>()->Handle();
        const auto window = static_cast<GLFWwindow*>(Window::Instance().NativeWindow());

        m_Surface.CreateSurface(instance, window);
    }

}