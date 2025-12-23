#include "Application.h"
#include "Systems/SystemManager.h"
#include "Systems/LogicalSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/RHISystem.h"
#include "Window/Window.h"
#include "World/World/World.h"
#include "World/Scene/Scene.h"

namespace PlayGround {

    static UP<Application> S_Instance = nullptr;

    Application& Application::Instance()
    {
        if(!S_Instance)
        {
            S_Instance = CreateUP<Application>();
            CORE_INFO("Application created.")
        }

        return *S_Instance;
    }

    void Application::Destroy()
    {
        S_Instance.reset();

        CORE_INFO("Application destroyed.")
    }

    Application::Application()
    {
        m_Window = Window::Create(WindowInfo{ 1200, 900, "PlayGround" }).get();

        m_SystemManager = CreateUP<SystemManager>();
        m_SystemManager
        ->PushSystem<LogicalSystem>()
        ->PushSystem<RenderSystem>()
        ->PushSystem<RHISystem>();

        m_World = World::Instance();
    }

    Application::~Application()
    {
        m_World.reset();

        m_SystemManager->PopAllSystems();

        Window::Destroy();

        Log::Reset();
    }

    void Application::Run()
    {
        m_World->OnAttached();

        while(m_Window->IsWindowActive())
        {
            m_Window->PollEvents();

            m_SystemManager->Run();

            m_Window->SwapBuffers();
        }

        m_World->OnDetached();
    }
}