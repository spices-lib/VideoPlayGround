#include "ScriptComponent.h"
#include "Scripts/ScriptInterface.h"
#include <ranges>

namespace PlayGround {

    void ScriptComponent::AddScript(const SP<ScriptInterface>& script)
    {
        if (m_Scripts.contains(script->GetUUID()))
        {
            CORE_WARN("Script is existing on component.")
            return;
        }

        script->OnAttached();
        m_Scripts[script->GetUUID()] = script;
    }
    
    void ScriptComponent::OnTick() const
    {
        for (const auto& script : m_Scripts | std::views::values)
        {
            script->OnTick();
        }
    }

    void ScriptComponent::OnEvent(Event& e) const
    {
        for (const auto& script : m_Scripts | std::views::values)
        {
            script->OnEvent(e);
        }
    }

    void ScriptComponent::OnComponentDetached()
    {
        for (const auto& script : m_Scripts | std::views::values)
        {
            script->OnDetached();
        }
    }
    
}