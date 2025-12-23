#pragma once
#include "Core/Core.h"
#include "Component.h"
#include "Core/Math/Transform.h"

namespace PlayGround {

    class TransformComponent : public Component
    {
    public:

        enum TransformComponentBits
        {
            Clean = 0,
            NeedUpdateTLAS = 1,
            MAX = 0x7FFFFFFF
        };

        typedef uint32_t TransformComponentFlags;

    public:

        TransformComponent();

        ~TransformComponent() override = default;

        void SetPosition(const glm::vec3& position) { m_Transform.position = position; CalMatrix(); }

        void SetRotation(const glm::vec3& rotation) { m_Transform.rotation = rotation; CalMatrix(); }

        void SetScale(const glm::vec3& scale) { m_Transform.scale = scale; CalMatrix(); }

        void AddPosition(const glm::vec3& position) { m_Transform.position += position; CalMatrix(); }

        void AddRotation(const glm::vec3& rotation) { m_Transform.rotation += rotation; CalMatrix(); }

        void AddScale(const glm::vec3& scale) { m_Transform.scale += scale; CalMatrix(); }

        const glm::mat4& GetModelMatrix() { CalMatrix(); return m_ModelMatrix; }

        glm::mat4 GetRotateMatrix() const;

        const glm::vec3& GetPosition() const { return m_Transform.position; }

        const glm::vec3& GetRotation() const { return m_Transform.rotation; }

        const glm::vec3& GetScale() const { return m_Transform.scale; }

        TransformComponentFlags GetMarker() const { return m_Marker; }

        void Mark(TransformComponentFlags flags) { m_Marker |= flags; }

        void ClearMarkerWithBits(TransformComponentFlags flags);

    private:

        void CalMatrix();

    private:

        glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

        Transform m_Transform;

        TransformComponentFlags m_Marker = TransformComponentBits::Clean;
    };
}