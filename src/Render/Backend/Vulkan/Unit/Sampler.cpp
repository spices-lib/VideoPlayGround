#include "Sampler.h"

namespace PlayGround::Vulkan::Unit {

	Sampler::~Sampler()
	{
		if (!m_Handle) return;

		vkDestroySampler(m_Device, m_Handle, nullptr);
	}

	void Sampler::CreateSampler(VkDevice device, const VkSamplerCreateInfo& info)
	{
		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateSampler(device, &info, nullptr, &m_Handle))
	}
}