#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Core/UUID.h"

#include <entt.hpp>
#include <shared_mutex>

namespace PlayGround {

    class Entity;

    class Scene : public NonCopyable
    {
    public:

        Scene();

        ~Scene() override = default;

        Entity Create(const std::string& name = "None");

        Entity Create(UUID uuid, const std::string& name = "None");

        void Destroy(const Entity& entity);

        Entity Query(uint32_t id);

        template<typename T, typename F>
        void ViewComponent(F&& fn) const;

        template<typename T, typename F>
        void ViewComponent(const std::vector<uint32_t>& ranges, F&& fn) const;

        template<typename T, typename F>
        void ViewComponent(const std::vector<uint32_t>& ranges, uint32_t floor, uint32_t ceil, F&& fn) const;

        template<typename F>
        void ViewRoot(F&& fn) const;

        template<typename T, typename... Args>
        T& AddComponent(uint32_t e, Args&&... args);

        template<typename T, typename... Args>
        T& ReplaceComponent(uint32_t e, Args&&... args);

        template<typename T>
        T& GetComponent(uint32_t e);

        template<typename T>
        void RemoveComponent(uint32_t e);

        template<typename T>
        bool HasComponent(uint32_t e) const;

    private:

        Entity CreateEmpty(UUID uuid);

        template<typename T>
        void OnComponentAttached(Entity* entity, T& component) const;

        template<typename T>
        void OnComponentDetached(Entity* entity, T& component) const;

    protected:

        mutable std::shared_mutex m_Mutex;

        entt::registry m_Registry;

        uint32_t m_Root;

        friend class Entity;
    };

    template <typename T, typename F>
    void Scene::ViewComponent(F&& fn) const
    {
        std::shared_lock<std::shared_mutex> lock(m_Mutex);

        const auto view = m_Registry.view<T>();

        for(const auto e : view)
        {
            const auto& comp = m_Registry.get<T>(e);

            if(!std::invoke(fn, static_cast<uint32_t>(e), comp)) break;
        }
    }

    template <typename T, typename F>
    void Scene::ViewComponent(const std::vector<uint32_t>& ranges, F&& fn) const
    {
        std::shared_lock<std::shared_mutex> lock(m_Mutex);

        for(const auto range : ranges)
        {
            const auto e = static_cast<entt::entity>(range);
            const auto& comp = m_Registry.get<T>(e);

            if (!std::invoke(fn, range, comp)) break;
        }
    }

    template<typename T, typename F>
    void Scene::ViewComponent(const std::vector<uint32_t>& ranges, uint32_t floor, uint32_t ceil, F&& fn) const
    {
        std::shared_lock<std::shared_mutex> lock(m_Mutex);
        
        assert(ceil >= floor);
        assert(ceil <= ranges.size() - 1);

        for(int32_t i = floor; i < ceil; i++)
        {
            const auto e = static_cast<entt::entity>(ranges[i]);
            const auto& comp = m_Registry.get<T>(e);

            if (!std::invoke(fn, ranges[i], comp)) break;
        }
    }

    template<typename F>
    void Scene::ViewRoot(F&& fn) const
    {
        std::shared_lock<std::shared_mutex> lock(m_Mutex);
        
        std::invoke(fn, m_Root);
    }

    template <typename T, typename ... Args>
    T& Scene::AddComponent(uint32_t e, Args&&... args)
    {
        std::unique_lock<std::shared_mutex> lock(m_Mutex);

        return m_Registry.emplace<T>(static_cast<entt::entity>(e), std::forward<Args>(args)...);
    }

    template <typename T, typename ... Args>
    T& Scene::ReplaceComponent(uint32_t e, Args&&... args)
    {
        std::unique_lock<std::shared_mutex> lock(m_Mutex);

        return m_Registry.replace<T>(static_cast<entt::entity>(e), std::forward<Args>(args)...);
    }

    template <typename T>
    T& Scene::GetComponent(uint32_t e)
    {
        /**
        * @note lock cause bug here.
        */
        //std::shared_lock<std::shared_mutex> lock(m_Mutex);

        return m_Registry.get<T>(static_cast<entt::entity>(e));
    }

    template <typename T>
    void Scene::RemoveComponent(uint32_t e)
    {
        std::unique_lock<std::shared_mutex> lock(m_Mutex);

        m_Registry.remove<T>(static_cast<entt::entity>(e));
    }

    template <typename T>
    bool Scene::HasComponent(uint32_t e) const
    {
        std::shared_lock<std::shared_mutex> lock(m_Mutex);

        return m_Registry.all_of<T>(static_cast<entt::entity>(e));
    }

    template<typename T>
    void Scene::OnComponentAttached(Entity* entity, T& component) const
    {
        component.OnComponentAttached(*entity);
    }

    template <typename T>
    void Scene::OnComponentDetached(Entity* entity, T& component) const
    {
        component.OnComponentDetached(*entity);
    }
}
