#include "TransformComponent.h"

namespace PlayGround {

    TransformComponent::TransformComponent()
            : Component()
    {
        SetPosition({ 0.0f, 0.0f, 0.0f });
        SetRotation({ 0.0f, 0.0f, 0.0f });
        SetScale({ 1.0f, 1.0f, 1.0f });
    }

    glm::mat4 TransformComponent::GetRotateMatrix() const
    {
        return Transform::GetRotationMatrix(m_Transform.rotation);
    }

    void TransformComponent::ClearMarkerWithBits(TransformComponentFlags flags)
    {
        if (m_Marker & flags)
        {
            m_Marker ^= flags;
        }
    }

    void TransformComponent::CalMatrix()
    {
        m_ModelMatrix = m_Transform.ToMatrix();
    }
}
