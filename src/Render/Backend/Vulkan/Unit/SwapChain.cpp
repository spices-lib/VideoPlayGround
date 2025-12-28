#include "SwapChain.h"

namespace PlayGround::Vulkan::Unit {

	SwapChain::~SwapChain()
	{
		if (!m_Handle) return;

		vkDestroySwapchainKHR(m_Device, m_Handle, nullptr);
	}

	void SwapChain::CreateSwapchain(VkDevice device, const VkSwapchainCreateInfoKHR& createInfo)
	{
		assert(device && !m_Handle);

		m_Device = device;

		VK_CHECK(vkCreateSwapchainKHR(m_Device, &createInfo, nullptr, &m_Handle))
	}

	std::vector<VkImage> SwapChain::GetSwapchainImages(uint32_t imageCount) const
	{
		std::vector<VkImage> images(imageCount);

		VK_CHECK(vkGetSwapchainImagesKHR(m_Device, m_Handle, &imageCount, images.data()))

		return images;
	}

	VkResult SwapChain::GetNextImage(VkSemaphore semaphore, uint32_t& imageIndex) const
	{
		return vkAcquireNextImageKHR(m_Device, m_Handle, UINT64_MAX, semaphore, VK_NULL_HANDLE, &imageIndex);
	}
}