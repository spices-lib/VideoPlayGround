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
        void OnEvent(Event& event) override;

    private:

        bool OnEngineEvent(class EngineEvent& e);

    private:

        SP<RenderFrontend> m_RenderFrontend;
    };
}