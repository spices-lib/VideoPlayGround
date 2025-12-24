#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class Fence : public Unit<VkFence, VkObjectType::VK_OBJECT_TYPE_FENCE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		Fence() : Unit() {}

		~Fence() override;

		void CreateFence(VkDevice device, const VkFenceCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;
	};
}