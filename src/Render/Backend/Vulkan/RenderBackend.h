#pragma once
#include "Core/Core.h"
#include "Render/Frontend/RenderFrontend.h"

namespace PlayGround {

    class Window;
}

namespace PlayGround::Vulkan {

    class RenderBackend : public RenderFrontend
    {
    public:

        RenderBackend(Window* window);

        ~RenderBackend() override;

        void BeginFrame(class Scene* scene) override;

        void EndFrame(class Scene* scene) override;

        void RenderFrame(class Scene* scene) override;

        void Wait() override;

        void InitSlateModule() override;

    private:

        void RecreateSwapChain() override;

    private:

        class Context& GetContext();

        SP<class Context> m_Context;

        Window* m_Window;
    };
}