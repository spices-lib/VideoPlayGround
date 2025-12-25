#include "VideoSession.h"

namespace PlayGround::Vulkan::Unit {

	VideoSession::~VideoSession()
	{
		if (!m_Handle) return;

		vkDestroyVideoSessionKHR(m_Device, m_Handle, nullptr);
	}

	void VideoSession::SetFunctor(PFN_vkCreateVideoSessionKHR create, PFN_vkDestroyVideoSessionKHR destroy)
	{
		vkCreateVideoSessionKHR  = create;
		vkDestroyVideoSessionKHR = destroy;
	}

	void VideoSession::CreateVideoSession(VkDevice device, const VkVideoSessionCreateInfoKHR& createInfo)
	{
		assert(device && !m_Handle);

		m_Device = device;

		VK_CHECK(vkCreateVideoSessionKHR(m_Device, &createInfo, nullptr, &m_Handle));
	}
}