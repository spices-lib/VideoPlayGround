#include "SystemManager.h"

namespace PlayGround {

    SystemManager::SystemManager()
    {
        // Set Global EventCallBack
        Event::SetEventCallbackFn(BIND_EVENT_FN(SystemManager::OnEvent));
    }

    SystemManager* SystemManager::PopSystem()
    {
        m_Systems.back()->OnSystemShutDown();
        m_Systems.pop_back();

        return this;
    }

    void SystemManager::PopAllSystems()
    {
        for(auto& system : m_Systems)
        {
            PopSystem();
        }
    }

    void SystemManager::Run() const
    {
        for(auto& system : m_Systems)
        {
            system->Tick();
        }
    }

    void SystemManager::OnEvent(Event& event) const
    {
        for(auto& system : m_Systems)
        {
            system->OnEvent(event);
        }
    }
}