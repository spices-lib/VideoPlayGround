#pragma once
#include "Core/Core.h"
#include "Event.h"

namespace PlayGround {

    class WindowResizeEvent : public Event
    {
    public:

        WindowResizeEvent(uint32_t width, uint32_t height)
                : m_Width(width)
                , m_Height(height)
        {}

        virtual ~WindowResizeEvent() override = default;

        [[nodiscard]] const uint32_t& GetWidth() const { return m_Width; }
        [[nodiscard]] const uint32_t& GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;

            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:

        uint32_t m_Width;
        uint32_t m_Height;
    };

    class WindowCloseEvent : public Event
    {
    public:

        WindowCloseEvent() = default;
        virtual ~WindowCloseEvent() override = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class WindowResizeOverEvent : public Event
    {
    public:

        WindowResizeOverEvent(uint32_t width, uint32_t height)
                : m_Width(width)
                , m_Height(height)
        {}

        virtual ~WindowResizeOverEvent() override = default;

        [[nodiscard]] const uint32_t& GetWidth() const { return m_Width; }
        [[nodiscard]] const uint32_t& GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeOverEvent: " << m_Width << ", " << m_Height;

            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResizeOver)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:

        uint32_t m_Width;
        uint32_t m_Height;
    };
}