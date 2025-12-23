#pragma once
#include "Core/Core.h"
#include "System.h"

namespace PlayGround {

    class LogicalSystem : public System
    {
    public:

        LogicalSystem(){}
        ~LogicalSystem() override = default;

        void OnSystemInitialize() override {}
        void OnSystemShutDown() override {}
        void Tick() override;
        void OnEvent(Event& event) override;

    private:
        
    };
}