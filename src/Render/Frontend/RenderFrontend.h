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

        virtual void BeginFrame() = 0;
        virtual void EndFrame() = 0;
        virtual void RenderFrame() = 0;

    protected:

        RenderFrontend(){}

    protected:

    };
}