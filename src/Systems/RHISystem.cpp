#include "RHISystem.h"
#include "Render/Frontend/RenderFrontend.h"
#include "World/World/World.h"

namespace PlayGround {

    void RHISystem::OnSystemInitialize()
    {
        m_RenderFrontend = RenderFrontend::Create();
    }

    void RHISystem::OnSystemShutDown()
    {

    }

    void RHISystem::Tick()
    {
        auto scene = World::Instance()->GetScenes().at("main_level").get();

        m_RenderFrontend->BeginFrame(scene);

        m_RenderFrontend->RenderFrame(scene);

        m_RenderFrontend->EndFrame(scene);
    }


}