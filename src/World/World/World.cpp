#include "World.h"
#include "World/Scene/Scene.h"
#include "Core/Event/EngineEvent.h"
#include "Slate/SlateScope.h"
#include "EditorWorld.h"
#include "Slate/Slate.h"
#include <sstream>
#include <ranges>

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

    void World::OnAttached()
    {
        EngineEvent event(EngineEventBit::InitSlateModule);

        Event::GetEventCallbackFn()(event);
    }

    void World::OnLayout()
    {
        Slate::SlateScope::BeginScope();

        std::for_each(m_Slates.begin(), m_Slates.end(), [](const auto& slate){
            slate->OnTick();
        });

        Slate::SlateScope::EndScope();
    }

    void World::OnEvent(Event& e)
    {
        std::for_each(m_Slates.begin(), m_Slates.end(), [&](const auto& slate) {
            slate->OnEvent(e);
        });
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
