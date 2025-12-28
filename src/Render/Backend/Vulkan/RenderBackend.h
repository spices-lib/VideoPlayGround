#pragma once
#include "Core/Core.h"
#include "Render/Frontend/RenderFrontend.h"
#include <any>

namespace PlayGround {

    class Window;
}

namespace PlayGround::Vulkan {

    class RenderBackend : public RenderFrontend
    {
    public:

        RenderBackend(Window* window);

        ~RenderBackend() override = default;

        void OnInitialize() override;

        void OnShutDown() override;

        void BeginFrame(class Scene* scene) override;

        void EndFrame(class Scene* scene) override;

        void Wait() override;

        void InitSlateModule() override;

        std::any CreateRHI(RHI::ERHI e) override;

    private:

        void RecreateSwapChain() override;

    private:

        class Context& GetContext() const;

        SP<Context> m_Context;

        Window* m_Window;
    };
}