#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/Pipeline.h"
#include "Render/Backend/Vulkan/Unit/PipelineLayout.h"
#include "Render/Frontend/RHI/Pipeline.h"

namespace PlayGround::RHI {

	class RenderPass;
	class DescriptorList;
}

namespace PlayGround::Vulkan {

	class Pipeline : public ContextAccessor, public RHI::Pipeline::Impl
	{
	public:

		Pipeline(Context& context) : ContextAccessor(context), RHI::Pipeline::Impl() {}
		~Pipeline() override = default;

		void SetDefault() override;
		void SetRenderPass(SP<RHI::RenderPass> renderPass) override;
		void SetVertexAttributeLayout() override;
		void SetDescriptorList(SP<RHI::DescriptorList> descriptorList) override;
		void SetCullMode(CullMode mode) override;
		void SetShaders() override;
		void BuildGraphicPipeline() override;

	private:

		Unit::Pipeline m_Pipeline;

		VkPipelineInputAssemblyStateCreateInfo           m_InputAssemblyInfo{};
		VkPipelineViewportStateCreateInfo                m_ViewportInfo{};
		VkPipelineRasterizationStateCreateInfo           m_RasterizationInfo{};
		VkPipelineMultisampleStateCreateInfo             m_MultisampleInfo{};
		VkPipelineColorBlendStateCreateInfo              m_ColorBlendInfo{};
		VkPipelineDepthStencilStateCreateInfo            m_DepthStencilInfo{};
		std::vector<VkDynamicState>                      m_DynamicStateEnables{};
		VkPipelineDynamicStateCreateInfo                 m_DynamicStateInfo{};
		std::vector<VkVertexInputBindingDescription>     m_BindingDescriptions{};
		std::vector<VkVertexInputAttributeDescription>   m_AttributeDescriptions{};
		VkRenderPass                                     m_RenderPass{};

		Unit::PipelineLayout                             m_PipelineLayout{};

		VkViewport                                       m_Viewport{};
		VkRect2D                                         m_Scissor{};
	};
}