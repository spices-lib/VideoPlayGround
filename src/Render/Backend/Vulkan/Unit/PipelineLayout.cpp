#include "PipelineLayout.h"

namespace PlayGround::Vulkan::Unit {

	PipelineLayout::~PipelineLayout()
	{
		if (!m_Handle) return;

		vkDestroyPipelineLayout(m_Device, m_Handle, nullptr);
	}

	void PipelineLayout::CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo& info)
	{
		assert(device);

		m_Device = device;

		VK_CHECK(vkCreatePipelineLayout(device, &info, nullptr, &m_Handle))
	}

}