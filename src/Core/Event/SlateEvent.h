#pragma once
#include "Core/Core.h"
#include "Event.h"

namespace PlayGround {

    class SlateResizeEvent : public Event
    {
    public:

        SlateResizeEvent(uint32_t width, uint32_t height)
                : m_Width(width)
                , m_Height(height)
        {}

        ~SlateResizeEvent() override = default;

        [[nodiscard]] const uint32_t& GetWidth() const { return m_Width; }
        [[nodiscard]] const uint32_t& GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "SlateResizeEvent: " << m_Width << ", " << m_Height;

            return ss.str();
        }

        EVENT_CLASS_TYPE(SlateResize)
        EVENT_CLASS_CATEGORY(EventCategorySlate)

    private:

        uint32_t m_Width;
        uint32_t m_Height;
    };
}