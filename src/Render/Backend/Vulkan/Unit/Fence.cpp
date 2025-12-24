#include "Fence.h"

namespace PlayGround::Vulkan::Unit {

	Fence::~Fence()
	{
		if (!m_Handle) return;

		vkDestroyFence(m_Device, m_Handle, nullptr);
	}

	void Fence::CreateFence(VkDevice device, const VkFenceCreateInfo& info)
	{
		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateFence(device, &info, nullptr, &m_Handle))
	}

	void Fence::WaitFence() const
	{
		VK_CHECK(vkWaitForFences(m_Device, 1, &m_Handle, VK_TRUE, UINT64_MAX))
	}

	void Fence::ResetFence() const
	{
		VK_CHECK(vkResetFences(m_Device, 1, &m_Handle))
	}
}