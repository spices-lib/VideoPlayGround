#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class PipelineLayout : public Unit<VkPipelineLayout, VkObjectType::VK_OBJECT_TYPE_PIPELINE_LAYOUT>
	{
	public:

		using Handle = Unit::Handle;

	public:

		PipelineLayout() : Unit() {}

		~PipelineLayout() override;

		void CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;
	};
}