#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class Instance : public Unit<VkInstance, VkObjectType::VK_OBJECT_TYPE_INSTANCE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		Instance() : Unit() {}

		~Instance() override;

		void CreateInstance(const VkInstanceCreateInfo& createInfo);
	};
}