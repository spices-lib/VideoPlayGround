#include "CommandBuffer.h"

namespace PlayGround::Vulkan::Unit {

	CommandBuffer::~CommandBuffer()
	{
		if (!m_Handle) return;

		vkFreeCommandBuffers(m_Device, m_CommandPool, 1, &m_Handle);
	}

	void CommandBuffer::CreateCommandBuffer(VkDevice device, const VkCommandBufferAllocateInfo& info)
	{
		assert(device && info.commandPool);

		m_Device = device;
		m_CommandPool = info.commandPool;

		VK_CHECK(vkAllocateCommandBuffers(m_Device, &info, &m_Handle))
	}

	void CommandBuffer::Begin(const VkCommandBufferBeginInfo& info)
	{
		VK_CHECK(vkBeginCommandBuffer(m_Handle, &info))
	}

	void CommandBuffer::End()
	{
		VK_CHECK(vkEndCommandBuffer(m_Handle))
	}
}