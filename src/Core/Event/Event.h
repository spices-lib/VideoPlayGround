#pragma once
#include "Core/Core.h"
#include "Core/Container/BitSet.hpp"

#include <functional>
#include <sstream>

namespace PlayGround {

    enum class EventType : uint32_t
    {
        WindowClose            = 0,
        WindowResize           = 1,
        WindowResizeOver       = 2,
        WindowFocus            = 3,
        WindowLostFocus        = 4,
        WindowMoved            = 5,

        SlateResize            = 6,

        KeyPressed             = 7,
        KeyReleased            = 8,
        KeyTyped               = 9,

        MouseButtonPressed     = 10,
        MouseButtonReleased    = 11,
        MouseMoved             = 12,
        MouseScrolled          = 13,

        MeshAdded              = 14,

        ALL                  = 18,
    };

    enum class EventCategory : uint16_t
    {
        EventCategoryApplication  = 0,
        EventCategorySlate        = 1,
        EventCategoryInput        = 2,
        EventCategoryKeyboard     = 3,
        EventCategoryMouse        = 4,
        EventCategoryMouseButton  = 5,
        EventCategoryWorld        = 6,

        ALL                       = 7
    };

namespace Detail {

    template<typename... T>
    void SetEventCategories(BitSet<EventCategory>& flags, T... categories)
    {
        (flags.Set(categories, true), ...);
    }

}

    #define EVENT_CLASS_TYPE(type)                                                              \
	static    EventType          GetStaticType()                { return EventType::type; }     \
	virtual   EventType          GetEventType()  const override { return GetStaticType(); }     \
	virtual   const std::string  GetName()       const override { return #type; }

    #define EVENT_CLASS_CATEGORY(...)                                        \
	virtual BitSet<EventCategory> GetCategoryFlags() const override          \
    {                                                                        \
        using enum EventCategory;                                            \
                                                                             \
        static BitSet<EventCategory> s_Category;                             \
                                                                             \
        if (s_Category.None())                                               \
        {                                                                    \
             Detail::SetEventCategories(s_Category, __VA_ARGS__);            \
        }                                                                    \
                                                                             \
        return s_Category;                                                   \
    }

    #define BIND_EVENT_FN(x)                                                 \
	std::bind(&x, this, std::placeholders::_1)

    class Event
    {
    public:

        virtual ~Event() = default;

        using EventCallbackFn = std::function<void(Event&)>;

        friend class EventDispatcher;

        virtual EventType               GetEventType()           const = 0;
        virtual const std::string       GetName()                const = 0;
        virtual BitSet<EventCategory>   GetCategoryFlags()       const = 0;
        virtual std::string             ToString()               const { return GetName(); }

        [[nodiscard]] bool IsInCategory(EventCategory category) const
        {
            return GetCategoryFlags().Test(category);
        }

        static EventCallbackFn GetEventCallbackFn();
        static void SetEventCallbackFn(const EventCallbackFn& callback);

        bool Handled = false;
    };

    class EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool(T&)>;

    public:

        EventDispatcher(Event& event)
                :m_Event(event)
        {}

        template<typename T>
        bool Dispatch(EventFn<T> func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.Handled = func(*static_cast<T*>(&m_Event));

                return true;
            }

            return false;
        }

    private:

        Event& m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}