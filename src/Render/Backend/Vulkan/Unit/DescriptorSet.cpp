#include "DescriptorSet.h"

namespace PlayGround::Vulkan::Unit {

	DescriptorSet::~DescriptorSet()
	{
		if (!m_Handle) return;

		vkFreeDescriptorSets(m_Device, m_DescriptorPool, 1, &m_Handle);
	}

	void DescriptorSet::AllocateDescriptorSet(VkDevice device, const VkDescriptorSetAllocateInfo& info)
	{
		assert(device && info.descriptorPool);

		m_Device = device;
		m_DescriptorPool = info.descriptorPool;

		VK_CHECK(vkAllocateDescriptorSets(device, &info, &m_Handle))
	}

	void DescriptorSet::UpdateDescriptorSet(const VkWriteDescriptorSet& write)
	{
		vkUpdateDescriptorSets(m_Device, 1, &write, 0, nullptr);
	}
}