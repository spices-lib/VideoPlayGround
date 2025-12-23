#include "Entity.h"

namespace PlayGround {

    void Entity::Destroy() const
    {
        m_Scene->Destroy(*this);
    }

    const UUID& Entity::GetUUID() const
    {
        return GetComponent<UUIDComponent>().GetUUID();
    }
}
