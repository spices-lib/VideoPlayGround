#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class FrameBuffer : public Unit<VkFramebuffer, VkObjectType::VK_OBJECT_TYPE_FRAMEBUFFER>
	{
	public:

		using Handle = Unit::Handle;

	public:

		FrameBuffer() : Unit() {}

		~FrameBuffer() override;

		void CreateFrameBuffer(VkDevice device, const VkFramebufferCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;
	};
}