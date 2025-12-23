#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class SwapChain : public Unit<VkSwapchainKHR, VkObjectType::VK_OBJECT_TYPE_SWAPCHAIN_KHR>
	{
	public:

		using Handle = Unit::Handle;

	public:

		SwapChain(Handle handle) : Unit(handle) {}

		~SwapChain() override = default;
	};
}