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

		void CreateSwapchain(VkDevice device, const VkSwapchainCreateInfoKHR& createInfo);
		std::vector<VkImage> GetSwapchainImages(uint32_t imageCount) const;
		VkResult GetNextImage(VkSemaphore semaphore, uint32_t& imageIndex) const;

	private:

		VkDevice m_Device = nullptr;
	};
}