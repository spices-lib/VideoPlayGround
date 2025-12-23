#pragma once
#include "Core/Core.h"
#include "Event.h"
#include "Core/Input/MouseButtonCodes.h"

namespace PlayGround {

    class MouseMovedEvent : public Event
    {
    public:

        MouseMovedEvent(float x, float y)
                : m_MouseX(x)
                , m_MouseY(y)
        {}

        ~MouseMovedEvent() override = default;

        [[nodiscard]] const float& GetX() const { return m_MouseX; }

        [[nodiscard]] const float& GetY() const { return m_MouseY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << " ," << m_MouseY;

            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse, EventCategoryInput)

    private:

        float m_MouseX;
        float m_MouseY;
    };

    class MouseScrolledEvent : public Event
    {
    public:

        MouseScrolledEvent(float xOffset, float yOffset)
                : m_XOffset(xOffset)
                , m_YOffset(yOffset)
        {}

        ~MouseScrolledEvent() override = default;

        [[nodiscard]] const float& GetXOffset() const { return m_XOffset; }
        [[nodiscard]] const float& GetYOffset() const { return m_YOffset; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();

            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse, EventCategoryInput)

    private:

        float m_XOffset;
        float m_YOffset;
    };

    class MouseButtonEvent : public Event
    {
    public:

        virtual ~MouseButtonEvent() override = default;

        [[nodiscard]] const MouseCode& GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse, EventCategoryInput)

    protected:

        MouseButtonEvent(MouseCode button)
                : m_Button(button)
        {}

        MouseCode m_Button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:

        MouseButtonPressedEvent(MouseCode button)
                : MouseButtonEvent(button)
        {}

        ~MouseButtonPressedEvent() override = default;

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << Mouse::ToString(m_Button);

            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:

        MouseButtonReleasedEvent(MouseCode button)
                : MouseButtonEvent(button)
        {}

        ~MouseButtonReleasedEvent() override = default;

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << Mouse::ToString(m_Button);

            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}