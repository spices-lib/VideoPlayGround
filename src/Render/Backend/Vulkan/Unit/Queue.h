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

		Queue() : Unit() {}

		~Queue() override = default;

		void Submit(const VkSubmitInfo& info, VkFence fence = VK_NULL_HANDLE) const;

		void Wait() const;
	};
}