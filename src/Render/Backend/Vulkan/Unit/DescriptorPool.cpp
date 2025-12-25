#include "DescriptorPool.h"

namespace PlayGround::Vulkan::Unit {

	DescriptorPool::~DescriptorPool()
	{
		if (!m_Handle) return;

		vkDestroyDescriptorPool(m_Device, m_Handle, nullptr);
	}

	void DescriptorPool::CreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo& info)
	{
		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateDescriptorPool(device, &info, nullptr, &m_Handle))
	}
}