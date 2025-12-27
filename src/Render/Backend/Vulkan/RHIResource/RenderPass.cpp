#include "RenderPass.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Render/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Render/Backend/Vulkan/Infrastructure/SwapChain.h"
#include "Render/Backend/Vulkan/Unit/ImageView.h"

namespace PlayGround::Vulkan {

	void RenderPass::AddSwapChainAttachment()
	{
		VkAttachmentDescription                       description{};
		description.format                          = GetContext().Get<IPhysicalDevice>()->GetSwapChainProperty().format.format;
		description.samples                         = VK_SAMPLE_COUNT_1_BIT;
		description.loadOp                          = VK_ATTACHMENT_LOAD_OP_CLEAR;
		description.storeOp                         = VK_ATTACHMENT_STORE_OP_STORE;
		description.stencilLoadOp                   = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		description.stencilStoreOp                  = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		description.initialLayout                   = VK_IMAGE_LAYOUT_UNDEFINED;
		description.finalLayout                     = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
											        
		VkClearValue                                  clearValue{};
		clearValue.color                            = { 0.0f, 0.0f, 0.0f, 1.0f };

		VkPipelineColorBlendAttachmentState           colorBlend{};
		colorBlend.colorWriteMask                   = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
			                                          VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlend.blendEnable                      = VK_FALSE;
		colorBlend.srcColorBlendFactor              = VK_BLEND_FACTOR_ONE;
		colorBlend.dstColorBlendFactor              = VK_BLEND_FACTOR_ZERO;
		colorBlend.colorBlendOp                     = VK_BLEND_OP_ADD;
		colorBlend.srcAlphaBlendFactor              = VK_BLEND_FACTOR_ONE;
		colorBlend.dstAlphaBlendFactor              = VK_BLEND_FACTOR_ZERO;
		colorBlend.alphaBlendOp                     = VK_BLEND_OP_ADD;
											        
		VkAttachmentReference                         attachmentRef{};
		attachmentRef.attachment                    = 0;
		attachmentRef.layout                        = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		m_AttachmentDescriptions.emplace_back(description);
		m_ColorAttachmentReference.emplace_back(attachmentRef);
		m_ColorBlends.emplace_back(colorBlend);
		m_ClearValues.emplace_back(clearValue);

		StoreExtent(GetContext().Get<IPhysicalDevice>()->GetSwapChainProperty().surfaceSize);
	}

	void RenderPass::Build()
	{
		{
			VkSubpassDescription                          description{};
			description.pipelineBindPoint               = VK_PIPELINE_BIND_POINT_GRAPHICS;
			description.colorAttachmentCount            = m_ColorAttachmentReference.size();
			description.pColorAttachments               = m_ColorAttachmentReference.data();
			description.pDepthStencilAttachment         = nullptr;
			description.inputAttachmentCount            = 0;
			description.pInputAttachments               = nullptr;

			VkRenderPassCreateInfo		                  info{};
			info.sType                                  = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
			info.attachmentCount                        = m_AttachmentDescriptions.size();
			info.pAttachments                           = m_AttachmentDescriptions.data();
			info.subpassCount                           = 1;
			info.pSubpasses                             = &description;
			info.dependencyCount                        = 0;
			info.pDependencies                          = nullptr;
		
			m_RenderPass.CreateRenderPass(GetContext().Get<IDevice>()->Handle(), info);
		}

		const bool swapChianInUsed = m_ImageViews.size() < m_AttachmentDescriptions.size();

		for (size_t i = 0; i < MaxFrameInFlight; i++)
		{
			auto imageViews = m_ImageViews;

			if (swapChianInUsed)
			{
				imageViews.insert(imageViews.begin(), GetContext().Get<ISwapChain>()->GetView(i));
			}

			VkFramebufferCreateInfo						  info{};
			info.sType						            = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			info.renderPass					            = m_RenderPass.GetHandle();
			info.attachmentCount			            = imageViews.size();
			info.pAttachments				            = imageViews.data();
			info.width                                  = m_Extent.value().width;
			info.height                                 = m_Extent.value().height;
			info.layers                                 = 1;

			auto frameBuffer = CreateSP<Unit::FrameBuffer>();

			frameBuffer->CreateFrameBuffer(GetContext().Get<IDevice>()->Handle(), info);

			m_FrameBuffers.emplace_back(frameBuffer);
		}
	}

	void RenderPass::BeginRenderPass(const Unit::CommandBuffer& commandBuffer, uint32_t frameBufferIndex)
	{
		VkRenderPassBeginInfo                         info{};
		info.sType                                  = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		info.renderPass                             = Handle();
		info.framebuffer                            = m_FrameBuffers[frameBufferIndex]->GetHandle();
		info.renderArea.offset                      = { 0, 0 };
		info.renderArea.extent                      = m_Extent.value();
		info.clearValueCount                        = m_ClearValues.size();
		info.pClearValues                           = m_ClearValues.data();

		commandBuffer.BeginRenderPass(info, VK_SUBPASS_CONTENTS_INLINE);
	}

	void RenderPass::StoreExtent(const VkExtent2D& extent)
	{
		if (m_Extent.has_value()) return;

		m_Extent = extent;
	}
	
}
