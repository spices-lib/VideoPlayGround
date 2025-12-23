#pragma once
#include "Core/Core.h"
#include "World/World/World.h"

namespace PlayGround::Editor {

    class EditorWorld : public World
    {
    public:

        EditorWorld() = default;

        ~EditorWorld() override = default;

        void OnAttached() override;

        void OnDetached() override {}
        
    protected:
        
        void Layout() override;

    private:

        void CreateExampleScene();
        
    };
    
}