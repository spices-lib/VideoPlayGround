#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class CommandBuffer : public Unit<VkCommandBuffer, VkObjectType::VK_OBJECT_TYPE_COMMAND_BUFFER>
	{
	public:

		using Handle = Unit::Handle;

	public:

		CommandBuffer(Handle handle) : Unit(handle) {}

		~CommandBuffer() override = default;
	};
}