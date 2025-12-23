#pragma once
#include "Core/Core.h"
#include "Event.h"
#include "Core/Input/KeyCodes.h"

namespace PlayGround {

    class KeyEvent : public Event
    {
    public:

        ~KeyEvent() override = default;

        [[nodiscard]] const KeyCode& GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard, EventCategoryInput)

    protected:

        KeyEvent(KeyCode keycode)
                :m_KeyCode(keycode)
        {}

        KeyCode m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:

        KeyPressedEvent(KeyCode keycode, int repeatCount)
                : KeyEvent(keycode)
                , m_RepeatCount(repeatCount)
        {}

        virtual ~KeyPressedEvent() override = default;

        const int& GetRepeatCount() const { return m_RepeatCount; }

        virtual std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << Key::ToString(m_KeyCode) << " (" << m_RepeatCount << " repeats)";

            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:

        int m_RepeatCount;
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:

        KeyReleasedEvent(KeyCode keycode)
                : KeyEvent(keycode)
        {}

        virtual ~KeyReleasedEvent() override = default;

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << Key::ToString(m_KeyCode);

            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyEvent
    {
    public:

        KeyTypedEvent(KeyCode keycode)
                : KeyEvent(keycode)
        {}

        ~KeyTypedEvent() override = default;

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << Key::ToString(m_KeyCode);

            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}