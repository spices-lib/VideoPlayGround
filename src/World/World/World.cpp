#include "World.h"
#include "World/Scene/Scene.h"
#include "EditorWorld.h"
#include <sstream>

namespace PlayGround {

    SP<World> CreateWorld()
    {
        return CreateSP<Editor::EditorWorld>();
    }

    SP<World> World::Instance()
    {
        static auto s_World = CreateWorld();
        return s_World;
    }

    Scene* World::CreateScene(const std::string& name)
    {
        if (m_Scenes.contains(name))
        {
            std::stringstream ss;
            ss << "Scene: [ " << name << " ] already exists in world!";
            
            CORE_ERROR(ss.str())
            return nullptr;
        }

        m_Scenes.emplace(name, CreateUP<Scene>());
        return m_Scenes.at(name).get();
    }
    
}
