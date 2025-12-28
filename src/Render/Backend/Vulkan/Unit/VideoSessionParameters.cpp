#include "VideoSessionParameters.h"

namespace PlayGround::Vulkan::Unit {

	VideoSessionParameters::~VideoSessionParameters()
	{
		if (!m_Handle) return;

		vkDestroyVideoSessionParametersKHR(m_Device, m_Handle, nullptr);
	}

	void VideoSessionParameters::SetFunctor(PFN_vkCreateVideoSessionParametersKHR create, PFN_vkDestroyVideoSessionParametersKHR destroy, PFN_vkUpdateVideoSessionParametersKHR update)
	{
		vkCreateVideoSessionParametersKHR  = create;
		vkDestroyVideoSessionParametersKHR = destroy;
		vkUpdateVideoSessionParametersKHR  = update;
	}

	void VideoSessionParameters::CreateVideoSessionParameters(VkDevice device, const VkVideoSessionParametersCreateInfoKHR& createInfo)
	{
		assert(device && !m_Handle);

		m_Device = device;

		VK_CHECK(vkCreateVideoSessionParametersKHR(m_Device, &createInfo, nullptr, &m_Handle));
	}

	void VideoSessionParameters::UpdateVideoSessionParameters(VkDevice device, const VkVideoSessionParametersUpdateInfoKHR& updateInfo) const
	{
		VK_CHECK(vkUpdateVideoSessionParametersKHR(m_Device, m_Handle, &updateInfo))
	}
}