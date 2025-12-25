#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class Pipeline : public Unit<VkPipeline, VkObjectType::VK_OBJECT_TYPE_PIPELINE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		Pipeline() : Unit() {}

		~Pipeline() override;

		void CreateGraphicPipeline(VkDevice device, const VkGraphicsPipelineCreateInfo& info);

		void CreateComputePipeline(VkDevice device, const VkComputePipelineCreateInfo& info);

	private:

		VkDevice         m_Device = VK_NULL_HANDLE;
	};
}