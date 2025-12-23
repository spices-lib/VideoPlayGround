#pragma once
#include "Core/Core.h"
#include "Core/Input/Input.h"

namespace PlayGround::GLFW {

    class InputImpl : public Input
    {
    protected:

        bool IsKeyPressedImpl(const int& keycode) override;
        bool IsMouseButtonPressedImpl(const int& button) override;
        std::pair<float, float> GetMousePositionImpl() override;
        float GetMouseXImpl() override;
        float GetMouseYImpl() override;
    };
}