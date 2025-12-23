#pragma once
#include "Core/Core.h"
#include "World/Scene/Scene.h"

#include "World/Component/UUIDComponent.h"

namespace PlayGround {

    class Entity
    {
    public:

        Entity(uint32_t handle, Scene* scene)
                : m_Handle(handle)
                , m_Scene(scene)
        {}

        virtual ~Entity() = default;

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args);

        template<typename T, typename... Args>
        T& ReplaceComponent(Args&&... args);

        template<typename T>
        T& GetComponent() const;

        template<typename T>
        void RemoveComponent() const;

        void Destroy() const;

        template<typename T>
        bool HasComponent() const;

        const UUID& GetUUID() const;

        operator uint32_t() const { return m_Handle; }

        bool operator ==(const Entity& other) const
        {
            return m_Handle == other.m_Handle && m_Scene == other.m_Scene;
        }

        bool operator !=(const Entity& other) const
        {
            return !operator==(other);
        }

    private:

        uint32_t m_Handle;

        Scene* m_Scene;
    };

    template <typename T, typename ... Args>
    T& Entity::AddComponent(Args&&... args)
    {
        if (HasComponent<T>())
        {
            std::stringstream ss;
            ss << "Entity: " << m_Handle << " already has such component.";

            CORE_WARN(ss.str())
            return GetComponent<T>();
        }

        T& component = m_Scene->AddComponent<T>(m_Handle, std::forward<Args>(args)...);
        m_Scene->OnComponentAttached<T>(this, component);
        return component;
    }

    template <typename T, typename ... Args>
    T& Entity::ReplaceComponent(Args&&... args)
    {
        if (!HasComponent<T>())
        {
            return AddComponent<T>(std::forward<Args>(args)...);
        }

        T& component = m_Scene->ReplaceComponent<T>(m_Handle, std::forward<Args>(args)...);
        m_Scene->OnComponentAttached<T>(this, component);
        return component;
    }

    template <typename T>
    T& Entity::GetComponent() const
    {
        return m_Scene->GetComponent<T>(m_Handle);
    }

    template <typename T>
    void Entity::RemoveComponent() const
    {
        if (!HasComponent<T>())
        {
            std::stringstream ss;
            ss << "Entity: " << m_Handle << " does not have such component.";

            CORE_WARN(ss.str())
            return;
        }

        T& component = GetComponent<T>();
            
        m_Scene->OnComponentDetached<T>(this, component);
        m_Scene->RemoveComponent<T>(m_Handle);
    }

    template <typename T>
    bool Entity::HasComponent() const
    {
        return m_Scene->HasComponent<T>(m_Handle);
    }
}
