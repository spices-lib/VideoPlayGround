#include "EditorWorld.h"
#include "World/Scene/Scene.h"
#include "World/Entity/Entity.h"
#include "World/Component/TransformComponent.h"
#include "World/Component/ScriptComponent.h"
#include "Scripts/NativeScripts/EngineClock.h"
#include "Slate/ViewPort.h"

namespace PlayGround::Editor {

    void EditorWorld::OnAttached()
    {
        World::OnAttached();

        CreateExampleScene();

        SetFlag(WorldMarkBit::DynamicScriptTick, true);
        SetFlag(WorldMarkBit::DynamicScriptEvent, true);
    }

    void EditorWorld::CreateExampleScene()
    {
        const auto scene = CreateScene("main_level");

        auto& scriptComponent = scene->GetComponent<ScriptComponent>(scene->GetRoot());

        scriptComponent.AddScript(CreateSP<EngineClock>(scene));

        RegistrySlate<Slate::ViewPort>("ViewPort");
    }
}
