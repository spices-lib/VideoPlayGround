#include "Pipeline.h"

namespace PlayGround::Vulkan::Unit {

	Pipeline::~Pipeline()
	{
		if (!m_Handle) return;

		vkDestroyPipeline(m_Device, m_Handle, nullptr);
	}

	void Pipeline::CreateGraphicPipeline(VkDevice device, const VkGraphicsPipelineCreateInfo& info)
	{
		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &info, nullptr, &m_Handle))
	}

	void Pipeline::CreateComputePipeline(VkDevice device, const VkComputePipelineCreateInfo& info)
	{
		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateComputePipelines(device, VK_NULL_HANDLE, 1, &info, nullptr, &m_Handle))
	}
}