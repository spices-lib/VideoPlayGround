#pragma once
#include "Core/Core.h"
#include "System.h"

namespace PlayGround {

    class RenderFrontend;

    class RHISystem : public System
    {
    public:

        RHISystem() : System() {}
        ~RHISystem() override = default;

        void OnSystemInitialize() override;
        void OnSystemShutDown() override;
        void Tick() override;

    private:

        SP<RenderFrontend> m_RenderFrontend;
    };
}