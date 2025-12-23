#pragma once
#include "Core/Core.h"
#include "NonCopyable.h"

namespace PlayGround {

    class SystemManager;
    class Window;
    class World;

    class Application : public NonCopyable
    {
    public:
        
        static Application& Instance();
        static void Destroy();

    public:

        Application();
        ~Application() override;

        void Run();

    public:

        UP<SystemManager> m_SystemManager;
        Window* m_Window;                 
        SP<World> m_World;                
    };

}