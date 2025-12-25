#pragma once
#include "Core/Core.h"
#include "Event.h"
#include <Core/Container/BitSet.hpp>

namespace PlayGround {

    enum class EngineEventBit : uint32_t
    {
        StopTheGame = 0,
        InitSlateModule,

        Count
    };

    class EngineEvent : public Event
    {
    public:

        EngineEvent(const BitSet<EngineEventBit>& flag)
            : m_Flag(flag)
        {}

        EngineEvent(EngineEventBit bit)
            : m_Flag()
        {
            m_Flag.Set(bit, true);
        }

        ~EngineEvent() override = default;

        [[nodiscard]] bool Has(EngineEventBit bit) const { return m_Flag.Test(bit); }

        std::string ToString() const override
        {
            using enum EngineEventBit;

            std::stringstream ss;
            ss << "EngineEvent: ";

            if (m_Flag.Test(StopTheGame))
            {
                ss << "StopTheGame  ";
            }

            return ss.str();
        }

        EVENT_CLASS_TYPE(Engine)
        EVENT_CLASS_CATEGORY(EventCategorySlate)

    private:

        BitSet<EngineEventBit> m_Flag;
    };
}