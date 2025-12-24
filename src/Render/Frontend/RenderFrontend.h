#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"

namespace PlayGround {

    class RenderFrontend : public NonCopyable
    {
    public:

        static SP<RenderFrontend> Create();

    public:

        ~RenderFrontend() override = default;

        virtual void BeginFrame(class Scene* scene) = 0;
        virtual void EndFrame(class Scene* scene) = 0;
        virtual void RenderFrame(class Scene* scene) = 0;

    protected:

        RenderFrontend(){}

        virtual  void RecreateSwapChain();

    protected:

    };
}