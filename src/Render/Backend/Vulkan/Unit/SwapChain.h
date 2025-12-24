#pragma once
#include "Core/Core.h"
#include "Unit.h"
#include <vector>

namespace PlayGround::Vulkan::Unit {

	class SwapChain : public Unit<VkSwapchainKHR, VkObjectType::VK_OBJECT_TYPE_SWAPCHAIN_KHR>
	{
	public:

		using Handle = Unit::Handle;

	public:

		SwapChain() : Unit() {}

		~SwapChain() override;

		void CreateSwapchain(VkDevice device, VkSwapchainCreateInfoKHR& createInfo);
		std::vector<VkImage> GetSwapchainImages(uint32_t imageCount);

	private:

		VkDevice m_Device = nullptr;
	};
}