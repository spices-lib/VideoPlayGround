#include "Scene.h"
#include "World/Entity/Entity.h"
#include "World/Component/ScriptComponent.h"
#include "World/Component/TagComponent.h"
#include "World/Component/UUIDComponent.h"

namespace PlayGround {
    
    Scene::Scene()
    {
        auto root = Create("SceneRoot");

        root.AddComponent<ScriptComponent>();

        m_Root = root;
    }

    Entity Scene::Create(const std::string& name)
    {
        return Create(UUID(), name);
    }

    Entity Scene::Create(UUID uuid, const std::string& name)
    {
        Entity entity = CreateEmpty(uuid);

        entity.AddComponent<UUIDComponent>(uuid);
        entity.AddComponent<TagComponent>(name);

        return entity;
    }

    void Scene::Destroy(const Entity& entity)
    {
        std::unique_lock<std::shared_mutex> lock(m_Mutex);

        uint32_t e = entity;
        m_Registry.destroy(static_cast<entt::entity>(e));
    }

    Entity Scene::Query(const uint32_t id)
    {
        return { id, this };
    }

    Entity Scene::CreateEmpty(const UUID uuid)
    {
        std::unique_lock<std::shared_mutex> lock(m_Mutex);

        return { static_cast<uint32_t>(m_Registry.create()), this };
    }
}
