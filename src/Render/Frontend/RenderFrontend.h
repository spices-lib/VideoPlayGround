#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Core/Event/Event.h"
#include "RHI/RHI.h"
#include <vector>
#include <any>

namespace PlayGround {

    namespace Render {
    
        class Pass;
    }

    class RenderFrontend : public NonCopyable
    {
    public:

        static SP<RenderFrontend> Create();

    public:

        ~RenderFrontend() override;

        virtual void OnInitialize();
        virtual void OnShutDown();
        virtual void BeginFrame(class Scene* scene) = 0;
        virtual void EndFrame(class Scene* scene) = 0;
        void RenderFrame(class Scene* scene);
        virtual void Wait() = 0;
        virtual void InitSlateModule() = 0;
        virtual std::any CreateRHI(RHI::ERHI e) = 0;

    protected:

        RenderFrontend() = default;

        virtual void RecreateSwapChain();

    private:

        void ConstructDefaultPasses();

        void AddPass(SP<Render::Pass> pass);

    protected:

        std::vector<SP<Render::Pass>> m_RenderPasses;
    };
}