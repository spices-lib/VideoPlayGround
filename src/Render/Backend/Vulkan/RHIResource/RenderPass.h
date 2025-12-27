#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/RenderPass.h"
#include "Render/Backend/Vulkan/Unit/FrameBuffer.h"
#include "Render/Backend/Vulkan/Unit/CommandBuffer.h"
#include "Render/Frontend/RHI/RenderPass.h"
#include <vector>
#include <optional>

namespace PlayGround::Vulkan {

	class RenderPass : public ContextAccessor, public RHI::RenderPass::Impl
	{
	public:

		RenderPass(Context& context) : ContextAccessor(context), RHI::RenderPass::Impl() {}
		~RenderPass() override = default;

		void AddSwapChainAttachment() override;
		void Build() override;

		const VkRenderPass& Handle() const { return m_RenderPass.GetHandle(); }

		void BeginRenderPass(const Unit::CommandBuffer& commandBuffer, uint32_t frameBufferIndex);

	private:

		void StoreExtent(const VkExtent2D& extent);

	private:

		Unit::RenderPass                                  m_RenderPass;
		std::vector<SP<Unit::FrameBuffer>>                m_FrameBuffers;

		std::vector<VkAttachmentDescription>              m_AttachmentDescriptions;
		std::vector<VkAttachmentReference>                m_ColorAttachmentReference;
		std::vector<VkPipelineColorBlendAttachmentState>  m_ColorBlends;
		std::vector<VkClearValue>                         m_ClearValues;
		std::vector<VkImageView>                          m_ImageViews;
		std::optional<VkExtent2D>                         m_Extent;
	};
}