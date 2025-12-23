#pragma once
#include "Core/Core.h"
#include "Component.h"
#include "Core/UUID.h"

namespace PlayGround {

    class UUIDComponent : public Component
    {
    public:

        UUIDComponent(UUID uuid) : m_uuid(uuid) {}

        UUIDComponent() : m_uuid(UUID()) {}

        ~UUIDComponent() override = default;

        const UUID& GetUUID() const { return m_uuid; }

    private:

        UUID m_uuid;
    };
}