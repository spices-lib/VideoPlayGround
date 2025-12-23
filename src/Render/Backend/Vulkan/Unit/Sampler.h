#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class Sampler : public Unit<VkSampler, VkObjectType::VK_OBJECT_TYPE_SAMPLER>
	{
	public:

		using Handle = Unit::Handle;

	public:

		Sampler(Handle handle) : Unit(handle) {}

		~Sampler() override = default;
	};
}