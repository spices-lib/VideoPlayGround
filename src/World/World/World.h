#pragma once
#include "Core/Core.h"
#include "WorldMarkFlag.h"
#include "Core/Event/Event.h"
#include "Core/Container/BitSet.hpp"

#include <unordered_map>

namespace PlayGround {

    namespace Slate {

        class Slate;
    }

    class Scene;

    class World : public NonCopyable
    {
    public:

        static SP<World> Instance();

    public:

        World() = default;

        ~World() override = default;

        virtual void OnAttached();

        virtual void OnDetached() = 0;

        void OnLayout();

        void OnEvent(Event& e);

        const std::unordered_map<std::string, UP<Scene>>& GetScenes() const { return m_Scenes; }

        bool TestFlag(WorldMarkBit bit) const { return m_Flag.Test(bit); }

        template<typename T, typename... Args>
        void RegistrySlate(Args&&... args);

    protected:

        Scene* CreateScene(const std::string& name);

        void SetFlag(WorldMarkBit bit, bool value) { m_Flag.Set(bit, value); }

        void ResetFlag() { m_Flag.Reset(); }

    private:
        
        std::unordered_map<std::string, UP<Scene>> m_Scenes;

        BitSet<WorldMarkBit> m_Flag;

        std::vector<SP<Slate::Slate>> m_Slates;
    
    };

    SP<World> CreateWorld();
    
    template<typename T, typename ...Args>
    inline void World::RegistrySlate(Args && ...args)
    {
        m_Slates.emplace_back(CreateSP<T>(std::forward<Args>(args)...));
    }

}

extern PlayGround::SP<PlayGround::World> PlayGround::CreateWorld();