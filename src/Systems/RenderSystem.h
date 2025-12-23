#pragma once
#include "Core/Core.h"
#include "System.h"

namespace PlayGround {

    class RenderSystem : public System
    {
    public:

        RenderSystem() : System() {}
        ~RenderSystem() override = default;

        void OnSystemInitialize() override {}
        void OnSystemShutDown() override {}
        void Tick() override {}
    };
}