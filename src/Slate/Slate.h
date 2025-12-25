#pragma once
#include "Core/Core.h"
#include "Core/Event/Event.h"
#include <imgui.h>

namespace PlayGround::Slate {

    class Slate
    {
    public:

        Slate(const std::string& slateName)
            : m_SlateName(slateName)
        {}

        virtual ~Slate() = default;

        virtual void OnTick() = 0;

        virtual void OnEvent(Event& event) {}

    protected:

        std::string m_SlateName;
        ImVec2      m_SlateSize = { 1, 1 };

    };
}
