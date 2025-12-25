#include "RenderPass.h"

namespace PlayGround::Vulkan::Unit {

	RenderPass::~RenderPass()
	{
		if (!m_Handle) return;

		vkDestroyRenderPass(m_Device, m_Handle, nullptr);
	}

	void RenderPass::CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo& info)
	{
		assert(device);

		m_Device = device;

		VK_CHECK(vkCreateRenderPass(device, &info, nullptr, &m_Handle))
	}
}