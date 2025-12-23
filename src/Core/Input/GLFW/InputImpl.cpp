#include "InputImpl.h"
#include "Window/Window.h"

#include <GLFW/glfw3.h>

namespace PlayGround::GLFW {

    bool InputImpl::IsKeyPressedImpl(const int& keycode)
    {
        const auto window = static_cast<GLFWwindow*>(Window::Instance().NativeWindow());

        const auto state = glfwGetKey(window, keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool InputImpl::IsMouseButtonPressedImpl(const int& button)
    {
        const auto window = static_cast<GLFWwindow*>(Window::Instance().NativeWindow());

        const auto state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS;
    }

    std::pair<float, float> InputImpl::GetMousePositionImpl()
    {
        const auto window = static_cast<GLFWwindow*>(Window::Instance().NativeWindow());

        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        return { static_cast<float>(xPos), static_cast<float>(yPos) };
    }

    float InputImpl::GetMouseXImpl()
    {
        auto [x, y] = GetMousePositionImpl();
        return x;
    }

    float InputImpl::GetMouseYImpl()
    {
        auto [x, y] = GetMousePositionImpl();
        return y;
    }
}