#pragma once

#include "Core/Core.h"

struct GLFWwindow;

namespace PlayGround::GLFW {

    class APIInterface
    {
    public:


        virtual void Hint() = 0;
        virtual void APILoad(GLFWwindow* handle) = 0;
        virtual void SwapBuffers(GLFWwindow* handle) = 0;
    };

    SP<APIInterface> CreateInterface();

    class VulkanInterface : public APIInterface
    {
    public:

        void Hint() override;
        void APILoad(GLFWwindow* handle) override {}
        void SwapBuffers(GLFWwindow* handle) override {};
    };

}