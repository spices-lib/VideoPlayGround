#include "Buffer.h"

namespace PlayGround::Vulkan::Unit {

	Buffer::~Buffer()
	{
		if (!m_Handle) return;

		vkDestroyBuffer(m_Device, m_Handle, nullptr);

		if (!m_Memory) return;

		vkFreeMemory(m_Device, m_Memory, nullptr);
	}

	void Buffer::CreateBuffer(VkDevice device, const VkBufferCreateInfo& info)
	{
		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateBuffer(device, &info, nullptr, &m_Handle))
	}
}