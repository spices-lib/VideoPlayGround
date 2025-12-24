#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class PhysicalDevice : public Unit<VkPhysicalDevice, VkObjectType::VK_OBJECT_TYPE_PHYSICAL_DEVICE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		PhysicalDevice() : Unit() {}

		~PhysicalDevice() override = default;
	};
}