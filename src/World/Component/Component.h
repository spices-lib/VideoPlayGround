#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Core/Event/Event.h"

namespace PlayGround {

    class Component : public NonCopyable
    {
    public:

        Component() = default;
        virtual ~Component() = default;

        virtual void OnComponentAttached(uint32_t entity);
        virtual void OnComponentDetached();

    protected:

        uint32_t m_Owner = 0;
    };

}
