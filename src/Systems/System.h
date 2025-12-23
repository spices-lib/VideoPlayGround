#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Core/Event/Event.h"

namespace PlayGround {

    class System : public NonCopyable
    {
    public:

        System() = default;
        ~System() override = default;

        virtual void OnSystemInitialize() = 0;
        virtual void OnSystemShutDown() = 0;
        virtual void Tick() = 0;
        virtual void OnEvent(Event& event) {}
    };
}