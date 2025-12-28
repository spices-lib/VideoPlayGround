#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class DescriptorSetLayout : public Unit<VkDescriptorSetLayout, VkObjectType::VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT>
	{
	public:

		using Handle = Unit::Handle;

	public:

		DescriptorSetLayout() : Unit() {}

		~DescriptorSetLayout() override;

		void CreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;
	};
}