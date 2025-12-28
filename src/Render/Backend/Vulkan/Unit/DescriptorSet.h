#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class DescriptorSet : public Unit<VkDescriptorSet, VkObjectType::VK_OBJECT_TYPE_DESCRIPTOR_SET>
	{
	public:

		using Handle = Unit::Handle;

	public:

		DescriptorSet() : Unit() {}

		~DescriptorSet() override;

		void AllocateDescriptorSet(VkDevice device, const VkDescriptorSetAllocateInfo& info);

		void UpdateDescriptorSet(const VkWriteDescriptorSet& write);

	private:

		VkDevice             m_Device = VK_NULL_HANDLE;
		VkDescriptorPool     m_DescriptorPool = VK_NULL_HANDLE;
	};
}