#pragma once
#include "Core/Core.h"
#include "Core/Event/Event.h"

namespace PlayGround {

    class Slate
    {
    public:

        Slate(std::string slateName)
                : m_SlateName(std::move(slateName))
        {}

        virtual ~Slate() = default;

        virtual void OnTick() = 0;
        virtual void OnEvent(Event& event) = 0;

    protected:

        std::string m_SlateName;
    };
}
