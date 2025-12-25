#include "FrameBuffer.h"

namespace PlayGround::Vulkan::Unit {

	FrameBuffer::~FrameBuffer()
	{
		if (!m_Handle) return;

		vkDestroyFramebuffer(m_Device, m_Handle, nullptr);
	}

	void FrameBuffer::CreateFrameBuffer(VkDevice device, const VkFramebufferCreateInfo& info)
	{
		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateFramebuffer(device, &info, nullptr, &m_Handle))
	}
}