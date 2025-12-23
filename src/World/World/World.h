#pragma once
#include "Core/Core.h"
#include "WorldMarkFlag.h"
#include "Core/Container/BitSet.hpp"

#include <unordered_map>

namespace PlayGround {

    class Scene;

    class World : public NonCopyable
    {
    public:

        static SP<World> Instance();

    public:

        World() = default;

        ~World() override = default;

        virtual void OnAttached() = 0;

        virtual void OnDetached() = 0;

        const std::unordered_map<std::string, UP<Scene>>& GetScenes() const { return m_Scenes; }

        bool TestFlag(WorldMarkBit bit) const { return m_Flag.Test(bit); }

    protected:

        virtual void Layout() = 0;

        Scene* CreateScene(const std::string& name);

        void SetFlag(WorldMarkBit bit, bool value) { m_Flag.Set(bit, value); }

        void ResetFlag() { m_Flag.Reset(); }

    private:
        
        std::unordered_map<std::string, UP<Scene>> m_Scenes;

        BitSet<WorldMarkBit> m_Flag;
    
    };

    SP<World> CreateWorld();
    
}

extern PlayGround::SP<PlayGround::World> PlayGround::CreateWorld();