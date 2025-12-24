#include "Semaphore.h"

namespace PlayGround::Vulkan::Unit {

	Semaphore::~Semaphore()
	{
		if (!m_Handle) return;

		vkDestroySemaphore(m_Device, m_Handle, nullptr);
	}

	void Semaphore::CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo& info)
	{
		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateSemaphore(device, &info, nullptr, &m_Handle))
	}
}