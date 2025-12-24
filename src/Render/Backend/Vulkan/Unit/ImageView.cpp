#include "ImageView.h"

namespace PlayGround::Vulkan::Unit {

	ImageView::~ImageView()
	{
		if (!m_Handle) return;

		vkDestroyImageView(m_Device, m_Handle, nullptr);
	}

	void ImageView::CreateImageView(VkDevice device, const VkImageViewCreateInfo& info)
	{
		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateImageView(m_Device, &info, nullptr, &m_Handle))
	}
}