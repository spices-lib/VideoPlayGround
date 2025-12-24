#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class Device : public Unit<VkDevice, VkObjectType::VK_OBJECT_TYPE_DEVICE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		Device() : Unit() {}

		~Device() override;

		void CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* createInfo);
		VkQueue GetDeviceQueue(uint32_t queueFamilyIndex, uint32_t queueIndex);
	};
}