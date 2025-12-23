#include "ScriptComponent.h"
#include "Scripts/ScriptInterface.h"
#include <ranges>

namespace PlayGround {

    void ScriptComponent::AddScript(const SP<ScriptInterface>& script)
    {
        if (m_Scripts.contains(script->GetFileString()))
        {
            CORE_WARN("Script is existing on component.")
            return;
        }

        script->OnAttached();
        m_Scripts[script->GetFileString()] = script;
    }

    void ScriptComponent::RemoveScript(const std::string& name)
    {
        if (!m_Scripts.contains(name))
        {
            CORE_WARN("Script is not existing on component.")
            return;
        }

        m_Scripts[name]->OnDetached();
        m_Scripts.erase(name);
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