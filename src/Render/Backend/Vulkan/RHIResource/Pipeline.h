#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/Pipeline.h"
#include "Render/Frontend/RHI/Pipeline.h"

namespace PlayGround::RHI {

	class RenderPass;
	class Descriptor;
}

namespace PlayGround::Vulkan {

	class Pipeline : public ContextAccessor, public RHI::Pipeline::Impl
	{
	public:

		Pipeline(Context& context) : ContextAccessor(context), RHI::Pipeline::Impl() {}
		~Pipeline() override = default;

		void SetDefault() override;
		void SetRenderPass(SP<RHI::RenderPass> renderPass) override;
		void SetDescriptor(SP<RHI::Descriptor> renderPass) override;
		void SetCullMode(CullMode mode) override;
		void SetShaders() override;
		void Build() override;

	private:

		Unit::Pipeline m_Pipeline;
	};
}