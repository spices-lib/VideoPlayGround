#pragma once
#include "Core/Core.h"
#include "Component.h"
#include "Data/Clock.h"

namespace PlayGround {

    class ClockComponent : public Component
    {
    public:

        ClockComponent() = default;

        ~ClockComponent() override = default;

        Data::Clock& GetClock() { return m_Clock; }
        const Data::Clock& GetClock() const { return m_Clock; }

    private:

        Data::Clock m_Clock;
    };
}