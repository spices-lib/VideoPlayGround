#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"

namespace PlayGround {

    class Input : public NonCopyable
    {
    public:

        Input() = default;
        ~Input() override = default;
  
        static bool IsKeyPressed(const int& keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
        static bool IsMouseButtonPressed(const int& button) { return s_Instance->IsMouseButtonPressedImpl(button); }
        static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
        static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
        static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

    protected:

        virtual bool IsKeyPressedImpl(const int& keycode) = 0;
        virtual bool IsMouseButtonPressedImpl(const int& button) = 0;
        virtual std::pair<float, float> GetMousePositionImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;

    private:

        static std::unique_ptr<Input> s_Instance;
    };

}