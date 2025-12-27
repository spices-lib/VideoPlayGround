#include "RHISystem.h"
#include "Render/Frontend/RenderFrontend.h"
#include "World/World/World.h"
#include "Core/Event/EngineEvent.h"

namespace PlayGround {

    void RHISystem::OnSystemInitialize()
    {
        m_RenderFrontend = RenderFrontend::Create();
    }

    void RHISystem::OnSystemShutDown()
    {
        m_RenderFrontend->OnShutDown();
    }

    void RHISystem::Tick()
    {
        auto scene = World::Instance()->GetScenes().at("main_level").get();

        m_RenderFrontend->BeginFrame(scene);

        m_RenderFrontend->RenderFrame(scene);

        m_RenderFrontend->EndFrame(scene);
    }

    void RHISystem::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<EngineEvent>(BIND_EVENT_FN(RHISystem::OnEngineEvent));
    }

    bool RHISystem::OnEngineEvent(EngineEvent& e)
    {
        if (e.Has(EngineEventBit::StopTheGame))
        {
            m_RenderFrontend->Wait();
        }

        if (e.Has(EngineEventBit::InitSlateModule))
        {
            m_RenderFrontend->InitSlateModule();
        }

        return false;
    }


}