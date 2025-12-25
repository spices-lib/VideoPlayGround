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

        const auto& scenes = world->GetScenes();

        if (world->TestFlag(WorldMarkBit::DynamicScriptTick))
        {
            for (const auto& scene : scenes | std::views::values)
            {
                scene->ViewComponent<ScriptComponent>([](uint32_t e, const ScriptComponent& comp) {

                    comp.OnTick();
                    return true;
                });
            }
        }

        world->OnLayout();
    }

    void LogicalSystem::OnEvent(Event& event)
    {
        const auto world = World::Instance();

        if (world->TestFlag(WorldMarkBit::DynamicScriptEvent))
        {
            const auto& scenes = World::Instance()->GetScenes();

            for (const auto& scene : scenes | std::views::values)
            {
                scene->ViewComponent<ScriptComponent>([&](uint32_t e, const ScriptComponent& comp) {

                    comp.OnEvent(event);
                    return true;
                });
            }
        }

        world->OnEvent(event);
    }
}
