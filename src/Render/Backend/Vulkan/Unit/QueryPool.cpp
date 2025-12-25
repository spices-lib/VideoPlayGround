#include "QueryPool.h"

namespace PlayGround::Vulkan::Unit {

	QueryPool::~QueryPool()
	{
		if (!m_Handle) return;

		vkDestroyQueryPool(m_Device, m_Handle, nullptr);
	}

	void QueryPool::CreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo& info)
	{
		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateQueryPool(device, &info, nullptr, &m_Handle))
	}
}