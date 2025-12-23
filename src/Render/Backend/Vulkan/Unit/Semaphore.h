#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class Semaphore : public Unit<VkSemaphore, VkObjectType::VK_OBJECT_TYPE_SEMAPHORE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		Semaphore(Handle handle) : Unit(handle) {}

		~Semaphore() override = default;
	};
}