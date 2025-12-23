#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class Surface : public Unit<VkSurfaceKHR, VkObjectType::VK_OBJECT_TYPE_SURFACE_KHR>
	{
	public:

		using Handle = Unit::Handle;

	public:

		Surface(Handle handle) : Unit(handle) {}

		~Surface() override = default;
	};
}