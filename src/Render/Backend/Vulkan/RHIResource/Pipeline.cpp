#include "Pipeline.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Render/Backend/Vulkan/RHIResource/RenderPass.h"
#include "Render/Backend/Vulkan/RHIResource/DescriptorList.h"
#include "Render/Backend/Vulkan/Converter.h"

namespace PlayGround::Vulkan {

	void Pipeline::SetDefault()
	{
		{
			VkPipelineInputAssemblyStateCreateInfo     info{};
			info.sType                               = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
			info.topology                            = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
			info.primitiveRestartEnable              = VK_FALSE;
			info.flags                               = 0;
			info.pNext                               = nullptr;

			m_InputAssemblyInfo                      = info;
		}

		{
			VkPipelineViewportStateCreateInfo          info{};
			info.sType                               = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
			info.viewportCount                       = 1;
			info.pViewports                          = &m_Viewport;
			info.scissorCount                        = 1;
			info.pScissors                           = &m_Scissor;

			m_ViewportInfo                           = info;
		}

		{
			VkPipelineRasterizationStateCreateInfo     info{};
			info.sType                               = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
			info.depthClampEnable                    = VK_FALSE;
			info.rasterizerDiscardEnable             = VK_FALSE;
			info.polygonMode                         = VK_POLYGON_MODE_FILL;
			info.lineWidth                           = 1.0f;
			info.cullMode                            = VK_CULL_MODE_BACK_BIT;
			info.frontFace                           = VK_FRONT_FACE_COUNTER_CLOCKWISE;
			info.depthBiasEnable                     = VK_FALSE;
			info.depthBiasConstantFactor             = 0.0f;
			info.depthBiasClamp                      = 0.0f;
			info.depthBiasSlopeFactor                = 0.0f;

			m_RasterizationInfo                      = info;
		}

		{
			VkPipelineMultisampleStateCreateInfo       info{};
			info.sType                               = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		    info.sampleShadingEnable                 = VK_FALSE;
		    info.rasterizationSamples                = VK_SAMPLE_COUNT_1_BIT;
		    info.minSampleShading                    = 1.0f;
		    info.pSampleMask                         = nullptr;
		    info.alphaToCoverageEnable               = VK_FALSE;
		    info.alphaToOneEnable                    = VK_FALSE;

			m_MultisampleInfo                        = info;
		}

		{
			VkPipelineColorBlendStateCreateInfo        info{};
			info.sType                               = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
			info.logicOpEnable                       = VK_FALSE;
			info.logicOp                             = VK_LOGIC_OP_COPY;						         
			info.attachmentCount                     = 0;
			info.pAttachments                        = nullptr;
			info.blendConstants[0]                   = 0.0f;
			info.blendConstants[1]                   = 0.0f;
			info.blendConstants[2]                   = 0.0f;
			info.blendConstants[3]                   = 0.0f;

			m_ColorBlendInfo                         = info;
		}

		{
			VkPipelineDepthStencilStateCreateInfo      info{};
			info.sType                               = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
			info.depthTestEnable                     = VK_TRUE;
			info.depthWriteEnable                    = VK_TRUE;
			info.depthCompareOp                      = VK_COMPARE_OP_GREATER_OR_EQUAL;
			info.depthBoundsTestEnable               = VK_FALSE;
			info.minDepthBounds                      = 0.0f;
			info.maxDepthBounds                      = 1.0f;
			info.stencilTestEnable                   = VK_FALSE;
			info.front                               = {};
			info.back                                = {};

			m_DepthStencilInfo                       = info;
		}

		{
			m_DynamicStateEnables                    = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
		}

		{
			VkPipelineDynamicStateCreateInfo           info{};
			info.sType                               = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
			info.pDynamicStates                      = m_DynamicStateEnables.data();
			info.dynamicStateCount                   = m_DynamicStateEnables.size();
			info.flags                               = 0;

			m_DynamicStateInfo                       = info;
		}
	}

	void Pipeline::SetRenderPass(SP<RHI::RenderPass> renderPass)
	{
		auto& colorBlends = renderPass->GetRHIImpl<RenderPass>()->GetColorBlends();

		m_ColorBlendInfo.attachmentCount = colorBlends.size();
		m_ColorBlendInfo.pAttachments    = colorBlends.data();

		m_RenderPass = renderPass->GetRHIImpl<RenderPass>()->Handle();
	}

	void Pipeline::SetVertexAttributeLayout()
	{

	}

	void Pipeline::SetDescriptorList(SP<RHI::DescriptorList> descriptorList)
	{

	}

	void Pipeline::SetCullMode(CullMode mode)
	{
		m_RasterizationInfo.cullMode = ToVkCullModeFlags(mode);
	}

	void Pipeline::SetShaders()
	{

	}

	void Pipeline::BuildGraphicPipeline()
	{
		VkPipelineVertexInputStateCreateInfo                  inputInfo{};
		inputInfo.sType                                     = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		inputInfo.vertexAttributeDescriptionCount           = m_AttributeDescriptions.size();
		inputInfo.vertexBindingDescriptionCount             = m_BindingDescriptions.size();
		inputInfo.pVertexAttributeDescriptions              = m_AttributeDescriptions.empty() ? nullptr : m_AttributeDescriptions.data();
		inputInfo.pVertexBindingDescriptions                = m_BindingDescriptions.empty() ? nullptr : m_BindingDescriptions.data();

		VkGraphicsPipelineCreateInfo                          info{};
		info.sType                                          = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		info.flags                                          = 0;
		//info.stageCount                                     = static_cast<uint32_t>(shaderStages.size());
		//info.pStages                                        = shaderStages.data();
		info.pVertexInputState                              = &inputInfo;
		info.pInputAssemblyState                            = &m_InputAssemblyInfo;
		info.pViewportState                                 = &m_ViewportInfo;
		info.pRasterizationState                            = &m_RasterizationInfo;
		info.pMultisampleState                              = &m_MultisampleInfo;
		info.pColorBlendState                               = &m_ColorBlendInfo;
		info.pDepthStencilState                             = &m_DepthStencilInfo;
		info.pDynamicState                                  = &m_DynamicStateInfo;										        	    
		info.layout                                         = m_PipelineLayout.GetHandle();
		info.renderPass                                     = m_RenderPass;
		info.subpass                                        = 0;			        	    
		info.basePipelineIndex                              = -1;
		info.basePipelineHandle                             = VK_NULL_HANDLE;

		m_Pipeline.CreateGraphicPipeline(GetContext().Get<IDevice>()->Handle(), info);
	}
	
}
