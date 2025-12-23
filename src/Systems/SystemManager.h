#pragma once
#include "Core/Core.h"
#include "System.h"
#include <vector>

namespace PlayGround {

    class Event;

    class SystemManager : public NonCopyable
    {
    public:

        SystemManager();
    	~SystemManager() override = default;

        template<typename T, typename ...Args>
        SystemManager* PushSystem(Args&&... args);

        SystemManager* PopSystem();

        void PopAllSystems();

        void Run() const;

    private:

        void OnEvent(Event& event) const;

    private:

        std::vector<UP<System>> m_Systems;
    };

    template<typename T, typename ...Args>
	SystemManager* SystemManager::PushSystem(Args&&... args)
    {
        m_Systems.emplace_back(CreateUP<T>(std::forward<Args>(args)...));
        m_Systems.back()->OnSystemInitialize();

        return this;
    }
}