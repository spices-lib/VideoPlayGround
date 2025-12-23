#pragma once
#include "Core/Core.h"
#include "Component.h"
#include <map>

namespace PlayGround {

    class ScriptInterface;

    class ScriptComponent : public Component
    {
    public:

        ScriptComponent() = default;

        void AddScript(const SP<ScriptInterface>& script);

        void RemoveScript(const std::string& name);

        ~ScriptComponent() override = default;

        void OnTick() const;

        void OnEvent(Event& e) const;

        void OnComponentDetached() override;

    private:

        std::map<std::string, SP<ScriptInterface>> m_Scripts;
    };
}