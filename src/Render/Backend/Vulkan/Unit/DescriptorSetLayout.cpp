#include "DescriptorSetLayout.h"

namespace PlayGround::Vulkan::Unit {

	DescriptorSetLayout::~DescriptorSetLayout()
	{
		if (!m_Handle) return;

		vkDestroyDescriptorSetLayout(m_Device, m_Handle, nullptr);
	}

	void DescriptorSetLayout::CreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo& info)
	{
		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateDescriptorSetLayout(m_Device, &info, nullptr, &m_Handle))
	}
}