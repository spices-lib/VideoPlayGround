#pragma once
#include "Core/Core.h"
#include "Render/Frontend/RenderFrontend.h"

namespace PlayGround::Vulkan {

    class RenderBackend : public RenderFrontend
    {
    public:

        RenderBackend(class Window* window);

        ~RenderBackend() override;

        void BeginFrame() override;

        void EndFrame() override;

        void RenderFrame() override;

    private:

        SP<class Context> m_Context;
    };
}