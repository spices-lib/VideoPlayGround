#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/RenderPass.h"
#include "Render/Backend/Vulkan/Unit/FrameBuffer.h"
#include "Render/Frontend/RHI/RenderPass.h"
#include <vector>

namespace PlayGround::Vulkan {

	class RenderPass : public ContextAccessor, public RHI::RenderPass::Impl
	{
	public:

		RenderPass(Context& context) : ContextAccessor(context), RHI::RenderPass::Impl() {}
		~RenderPass() override = default;

		void AddSwapChainAttachment() override {}
		const void* GetRHIRenderPass() override;
		void Build() override;

	private:

		Unit::RenderPass m_RenderPass;
		std::vector<SP<Unit::FrameBuffer>> m_FrameBuffers;
	};
}