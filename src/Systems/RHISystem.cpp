#include "RHISystem.h"
#include "Render/Frontend/RenderFrontend.h"

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
        m_RenderFrontend->BeginFrame();
        m_RenderFrontend->RenderFrame();
        m_RenderFrontend->EndFrame();
    }


}