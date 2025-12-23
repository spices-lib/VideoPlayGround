#pragma once
#include "Core/Core.h"
#include "Unit.h"
#include <vector>

namespace PlayGround::Vulkan::Unit {

	class Queue : public Unit<VkQueue, VkObjectType::VK_OBJECT_TYPE_QUEUE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		Queue(Handle handle) : Unit(handle) {}

		~Queue() override = default;

		void Submit(class CommandBuffer commandBuffer) const;
		void Submit(const std::vector<CommandBuffer>& commandBuffers) const;

		void Wait() const;
	};
}