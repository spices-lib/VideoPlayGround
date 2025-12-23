#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include <string>

namespace PlayGround {

    struct WindowInfo
    {
        int width;
        int height;
        std::string name;
    };

    class Window : public NonCopyable
    {
    public:

        static SP<Window> Create(const WindowInfo& initInfo);
        static Window& Instance();
        static void Destroy();

    public:

        Window(const WindowInfo& initInfo);
        ~Window() override = default;

        virtual bool IsWindowActive() = 0;
        virtual void PollEvents() = 0;
        virtual void SwapBuffers() = 0;
        virtual void* NativeWindow() = 0;

    protected:

        WindowInfo m_WindowInfo;
        bool m_WindowsResized;
    };
}