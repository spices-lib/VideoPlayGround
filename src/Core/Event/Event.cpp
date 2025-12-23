#include "Event.h"

namespace PlayGround {

    static Event::EventCallbackFn EventCallback;

    Event::EventCallbackFn Event::GetEventCallbackFn()
    {
        return EventCallback;
    }

    void Event::SetEventCallbackFn(const EventCallbackFn& callback)
    {

        EventCallback = callback;
    }
}