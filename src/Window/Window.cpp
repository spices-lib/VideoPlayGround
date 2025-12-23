#include "Window.h"
#include "Window/GLFW/WindowImpl.h"
#include <cassert>

namespace PlayGround {

    static SP<Window> S_Instance = nullptr;

    SP<Window> Window::Create(const WindowInfo& initInfo)
    {
        S_Instance = CreateSP<GLFW::WindowImpl>(initInfo);
        return S_Instance;
    }

    Window& Window::Instance()
    {
        assert(S_Instance);
        return *S_Instance;
    }

    void Window::Destroy()
    {
        S_Instance.reset();
        S_Instance = nullptr;
    }

    Window::Window(const WindowInfo& initInfo)
        : m_WindowInfo(initInfo)
        , m_WindowsResized(false)
    {}

}