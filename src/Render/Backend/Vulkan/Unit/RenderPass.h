#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class RenderPass : public Unit<VkRenderPass, VkObjectType::VK_OBJECT_TYPE_RENDER_PASS>
	{
	public:

		using Handle = Unit::Handle;

	public:

		RenderPass() : Unit() {}

		~RenderPass() override;

		void CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;
	};
}