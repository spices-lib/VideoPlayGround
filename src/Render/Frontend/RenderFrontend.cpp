#include "RenderFrontend.h"
#include "Render/Backend/Vulkan/RenderBackend.h"
#include "Render/FrontEnd/Pass/BasePass.h"
#include "Render/FrontEnd/Pass/SlatePass.h"
#include "Render/FrontEnd/Pass/PrePass.h"
#include "Window/Window.h"
#include "Core/Event/WindowEvent.h"
#include "Render/FrontEnd/Pass/Pass.h"
#include <GLFW/glfw3.h>
#include "Render/Frontend/RHI/RHI.h"
#include <algorithm>

namespace PlayGround {

    SP<RenderFrontend> RenderFrontend::Create()
    {
        auto sp = CreateSP<Vulkan::RenderBackend>(&Window::Instance());

        RHI::RHIDelegate::SetCreator([p = sp.get()](RHI::ERHI e){ return p->CreateRHI(e); });

        sp->OnInitialize();
        
        return sp;
    }

    RenderFrontend::~RenderFrontend()
    {
        RHI::RHIDelegate::SetCreator(nullptr);
    }

    void RenderFrontend::OnInitialize()
    {
        ConstructDefaultPasses();
    }

    void RenderFrontend::OnShutDown()
    {
        m_RenderPasses = {};
    }

    void RenderFrontend::RenderFrame(Scene* scene)
    {
        std::for_each(m_RenderPasses.begin(), m_RenderPasses.end(), [&](const auto& renderPass) {
            renderPass->OnRender(scene);
        });
    }

    void RenderFrontend::RecreateSwapChain()
    {
        auto glfwWindow = static_cast<GLFWwindow*>(Window::Instance().NativeWindow());

        int width = 0, height = 0;
        glfwGetFramebufferSize(glfwWindow, &width, &height);

        while (width == 0 || height == 0)
        {
            glfwGetFramebufferSize(glfwWindow, &width, &height);
            glfwWaitEvents();
        }

        ConstructDefaultPasses();

        WindowResizeOverEvent event(width, height);

        Event::GetEventCallbackFn()(event);
    }

    void RenderFrontend::ConstructDefaultPasses()
    {
        m_RenderPasses = {};

        {
            auto prePass = CreateSP<Render::PrePass>();

            AddPass(prePass);
        }

        {
            auto bassPass = CreateSP<Render::BasePass>();

            AddPass(bassPass);
        }

        {
            auto slatePass = CreateSP<Render::SlatePass>();

            AddPass(slatePass);
        }
    }

    void RenderFrontend::AddPass(SP<Render::Pass> pass)
    {
        pass->OnConstruct();

        m_RenderPasses.emplace_back(pass);
    }

}