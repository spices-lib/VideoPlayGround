#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/Pipeline.h"
#include "Render/Frontend/RHI/Pipeline.h"

namespace PlayGround::Vulkan {

	class Pipeline : public ContextAccessor, public RHI::Pipeline::Impl
	{
	public:

		Pipeline(Context& context) : ContextAccessor(context), RHI::Pipeline::Impl() {}
		~Pipeline() override = default;

		void SetDefault() override;
		void SetRenderPass() override;
		void SetDescriptor() override;
		void SetCullMode() override;
		void SetShaders() override;
		void Build() override;

	private:

		Unit::Pipeline m_Pipeline;
	};
}