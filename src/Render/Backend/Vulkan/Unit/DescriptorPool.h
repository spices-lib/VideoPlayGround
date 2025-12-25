#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class DescriptorPool : public Unit<VkDescriptorPool, VkObjectType::VK_OBJECT_TYPE_DESCRIPTOR_POOL>
	{
	public:

		using Handle = Unit::Handle;

	public:

		DescriptorPool() : Unit() {}

		~DescriptorPool() override;

		void CreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo& info);

	private:

		VkDevice         m_Device = VK_NULL_HANDLE;
	};
}