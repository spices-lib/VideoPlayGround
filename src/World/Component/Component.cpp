#include "Component.h"

namespace PlayGround {

    void Component::OnComponentAttached(uint32_t entity)
    {
        m_Owner = entity;
    }

    void Component::OnComponentDetached()
    {}
}