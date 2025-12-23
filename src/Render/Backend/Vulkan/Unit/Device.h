#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class Device : public Unit<VkDevice, VkObjectType::VK_OBJECT_TYPE_DEVICE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		Device(Handle handle) : Unit(handle) {}

		~Device() override = default;
	};
}