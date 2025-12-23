#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class Fence : public Unit<VkFence, VkObjectType::VK_OBJECT_TYPE_FENCE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		Fence(Handle handle) : Unit(handle) {}

		~Fence() override = default;
	};
}