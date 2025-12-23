#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class CommandPool : public Unit<VkCommandPool, VkObjectType::VK_OBJECT_TYPE_COMMAND_POOL>
	{
	public:

		using Handle = Unit::Handle;

	public:

		CommandPool(Handle handle) : Unit(handle) {}

		~CommandPool() override = default;
	};
}