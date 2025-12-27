#include "SwapChain.h"
#include "Surface.h"
#include "Render/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Render/Backend/Vulkan/Infrastructure/Queue.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include <GLFW/glfw3.h>

namespace PlayGround::Vulkan {

    SwapChain::SwapChain(Context& context, EInfrastructure e, GLFWwindow* window, uint32_t count)
        : Infrastructure(context, e)
    {
        Create(window, count);
    }

	void SwapChain::Destroy()
	{
		m_SwapChainImage.clear();
		m_SwapChain.reset();
	}

	void SwapChain::Create(GLFWwindow* window, uint32_t count)
    {
		auto physicalDevice = GetContext().Get<IPhysicalDevice>();
		auto& property = physicalDevice->QuerySwapChainProperty(window);

        VkSwapchainCreateInfoKHR                 createInfo{};
		createInfo.sType                       = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface                     = GetContext().Get<ISurface>()->Handle();
		createInfo.minImageCount               = count;
		createInfo.imageFormat                 = property.format.format;
		createInfo.imageColorSpace             = property.format.colorSpace;
		createInfo.imageExtent                 = property.surfaceSize;
		createInfo.imageArrayLayers            = 1;
		createInfo.imageUsage                  = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;

		uint32_t queueFamilyIndices[2] = 
		{ 
			physicalDevice->GetQueueFamilies().graphic.value(),
			physicalDevice->GetQueueFamilies().present.value()
		};

		if (queueFamilyIndices[0] != queueFamilyIndices[1])
		{
			createInfo.imageSharingMode        = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount   = 2;
			createInfo.pQueueFamilyIndices     = queueFamilyIndices;
		}
		else 
		{
			createInfo.imageSharingMode        = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount   = 0;
			createInfo.pQueueFamilyIndices     = nullptr;
		}

		createInfo.preTransform                = property.capabilities.currentTransform;
		createInfo.compositeAlpha              = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode                 = property.presentMode;
		createInfo.clipped                     = VK_TRUE;
		createInfo.oldSwapchain                = VK_NULL_HANDLE;

		m_SwapChain = CreateSP<Unit::SwapChain>();
		m_SwapChain->CreateSwapchain(GetContext().Get<IDevice>()->Handle(), createInfo);
		DEBUGUTILS_SETOBJECTNAME(*m_SwapChain, "SpicesEngineSwapChainKHR")

		uint32_t imageCount = count;
		auto images = m_SwapChain->GetSwapchainImages(imageCount);

		for (size_t i = 0; i < count; i++)
		{
			auto swapChainImage = CreateSP<Image>(GetContext());
			swapChainImage->SetImage(images[i]);

			m_SwapChainImage.emplace_back(swapChainImage);
			
			{
				VkImageViewCreateInfo info{};
				info.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;

				info.viewType = VK_IMAGE_VIEW_TYPE_2D;
				info.format   = property.format.format;

				info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
				info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
				info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
				info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

				info.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
				info.subresourceRange.baseMipLevel   = 0;
				info.subresourceRange.levelCount     = 1;
				info.subresourceRange.baseArrayLayer = 0;
				info.subresourceRange.layerCount     = 1;

				swapChainImage->CreateImageView(GetContext().Get<IDevice>()->Handle(), info);
			}

			{
				VkSamplerCreateInfo samplerInfo{};
				samplerInfo.sType            = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
				samplerInfo.magFilter        = VK_FILTER_LINEAR;
				samplerInfo.minFilter        = VK_FILTER_LINEAR;
				samplerInfo.addressModeU     = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				samplerInfo.addressModeV     = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				samplerInfo.addressModeW     = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				samplerInfo.anisotropyEnable = VK_TRUE;

				VkPhysicalDeviceProperties properties{};
				vkGetPhysicalDeviceProperties(GetContext().Get<IPhysicalDevice>()->Handle(), &properties);

				samplerInfo.maxAnisotropy           = properties.limits.maxSamplerAnisotropy;
				samplerInfo.borderColor             = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
				samplerInfo.unnormalizedCoordinates = VK_FALSE;
				samplerInfo.compareEnable           = VK_FALSE;
				samplerInfo.compareOp               = VK_COMPARE_OP_ALWAYS;

				samplerInfo.mipmapMode              = VK_SAMPLER_MIPMAP_MODE_LINEAR;
				samplerInfo.mipLodBias              = 0.0f;
				samplerInfo.minLod                  = 0.0f;
				samplerInfo.maxLod                  = static_cast<float>(0);

				swapChainImage->CreateSampler(GetContext().Get<IDevice>()->Handle(), samplerInfo);
			}

			swapChainImage->SetName("SwapChain");
		}
    }

	bool SwapChain::GetNextImage(VkSemaphore semaphore, uint32_t& imageIndex)
	{
		const auto result = m_SwapChain->GetNextImage(semaphore, imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			return false;
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		{
			CORE_ERROR("Failed to Acquire SwapChain Image.")
		}

		return true;
	}

	bool SwapChain::Present(VkPresentInfoKHR& info)
	{
		info.pSwapchains = &Handle();

		const auto result = vkQueuePresentKHR(GetContext().Get<IPresentQueue>()->Handle(), &info);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
		{
			return false;
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
		{
			CORE_ERROR("Failed to Present SwapChain Image.")
		}

		return true;
	}

	void SwapChain::ReCreate(GLFWwindow* window, uint32_t count)
	{
		Destroy();
		Create(window, count);
	}
}