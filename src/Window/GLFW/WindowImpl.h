#pragma once

#include "Core/Core.h"
#include "Window/Window.h"

struct GLFWwindow;

namespace PlayGround::GLFW {

    class APIInterface;

    class WindowImpl : public Window
    {
    public:

        WindowImpl(const WindowInfo& initInfo);
        ~WindowImpl() override;


        bool IsWindowActive() override;
        void PollEvents() override;
        void SwapBuffers() override;
        void* NativeWindow() override;

    private:

        void SetInternalCallBack() const;

    private:
        
        GLFWwindow* m_Windows;
        SP<APIInterface> m_APIInterface;
    };
}