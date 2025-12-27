#include "RenderPass.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"

namespace PlayGround::Vulkan {

	const void* RenderPass::GetRHIRenderPass()
	{
		return &m_RenderPass.GetHandle();
	}

	void RenderPass::Build()
	{
		VkRenderPassCreateInfo		   info{};
		info.sType                   = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		info.subpassCount            = 1;
		info.pSubpasses              = nullptr;
		
		m_RenderPass.CreateRenderPass(GetContext().Get<IDevice>()->Handle(), info);
	}
	
}
