#include "Device.h"

namespace PlayGround::Vulkan::Unit {

	Device::~Device()
	{
		if (!m_Handle) return;

		vkDestroyDevice(m_Handle, nullptr);
	}

	void Device::CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* createInfo)
	{
		assert(physicalDevice && createInfo && !m_Handle);

		VK_CHECK(vkCreateDevice(physicalDevice, createInfo, nullptr, &m_Handle))
	}

	VkQueue Device::GetDeviceQueue(uint32_t queueFamilyIndex, uint32_t queueIndex) const
	{
		VkQueue queue{};

		vkGetDeviceQueue(m_Handle, queueFamilyIndex, queueIndex, &queue);

		assert(queue);

		return queue;
	}

	void Device::Wait() const
	{
		VK_CHECK(vkDeviceWaitIdle(m_Handle))
	}
}