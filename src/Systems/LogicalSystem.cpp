#include "LogicalSystem.h"
#include "World/World/World.h"
#include "World/Scene/Scene.h"
#include "World/Component/ScriptComponent.h"

#include <ranges>

namespace PlayGround {
    
    void LogicalSystem::Tick()
    {
        // receive ui event or interface event.

        const auto world = World::Instance();

        if (!world->TestFlag(WorldMarkBit::DynamicScriptTick)) return;

        const auto& scenes = world->GetScenes();

        for (const auto& scene : scenes | std::views::values)
        {
            scene->ViewComponent<ScriptComponent>([](uint32_t e, const ScriptComponent& comp) {

                comp.OnTick();
                return true;
            });
        }
    }

    void LogicalSystem::OnEvent(Event& event)
    {
        const auto world = World::Instance();

        if (!world->TestFlag(WorldMarkBit::DynamicScriptEvent)) return;

        const auto& scenes = World::Instance()->GetScenes();

        for (const auto& scene : scenes | std::views::values)
        {
            scene->ViewComponent<ScriptComponent>([&](uint32_t e, const ScriptComponent& comp) {

                comp.OnEvent(event);
                return true;
            });
        }
    }
}
