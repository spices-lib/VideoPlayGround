#include "SwapChain.h"
#include "Surface.h"
#include "Render/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include <GLFW/glfw3.h>

namespace PlayGround::Vulkan {

    SwapChain::SwapChain(Context& context, GLFWwindow* window)
        : Infrastructure(context)
    {
        Create(window);
    }

    void SwapChain::Create(GLFWwindow* window)
    {
		auto physicalDevice = m_Context.Get<PhysicalDevice>();
		auto property = physicalDevice->QuerySwapChainSupport(window);

        VkSwapchainCreateInfoKHR                 createInfo{};
		createInfo.sType                       = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface                     = m_Context.Get<Surface>()->Handle();
		createInfo.minImageCount               = MaxFrameInFlight;
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

		VK_CHECK(vkCreateSwapchainKHR(m_Context.Get<Device>()->Handle(), &createInfo, nullptr, &m_Handle));
		DEBUGUTILS_SETOBJECTNAME(VK_OBJECT_TYPE_SWAPCHAIN_KHR, reinterpret_cast<uint64_t>(m_Handle), "SpicesEngineSwapChainKHR")

		uint32_t imageCount = MaxFrameInFlight;
		vkGetSwapchainImagesKHR(m_Context.Get<Device>()->Handle(), m_Handle, &imageCount, m_VulkanState.m_SwapChainImages.data());

		for (size_t i = 0; i < MaxFrameInFlight; i++) 
		{
			{
				/**
				* @brief Instance a VkImageViewCreateInfo.
				*/
				VkImageViewCreateInfo info{};
				info.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				info.image    = m_VulkanState.m_SwapChainImages[i];

				info.viewType = VK_IMAGE_VIEW_TYPE_2D;
				info.format   = m_VulkanDevice->GetSwapChainSupport().format.format;

				info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
				info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
				info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
				info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

				info.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
				info.subresourceRange.baseMipLevel   = 0;
				info.subresourceRange.levelCount     = 1;
				info.subresourceRange.baseArrayLayer = 0;
				info.subresourceRange.layerCount     = 1;

				DEBUGUTILS_SETOBJECTNAME(VK_OBJECT_TYPE_IMAGE, reinterpret_cast<uint64_t>(m_VulkanState.m_SwapChainImages[i]), m_VulkanState.m_Device, "SwapChainImage")

				VK_CHECK(vkCreateImageView(m_VulkanState.m_Device, &info, nullptr, &m_VulkanState.m_SwapChainImageViews[i]))
				DEBUGUTILS_SETOBJECTNAME(VK_OBJECT_TYPE_IMAGE_VIEW, reinterpret_cast<uint64_t>(m_VulkanState.m_SwapChainImageViews[i]), m_VulkanState.m_Device, "SwapChainImageView")
			}

			/**
			* @brief Create Sampler.
			*/
			{
				/**
				* @brief Instance a VkSamplerCreateInfo.
				*/
				VkSamplerCreateInfo samplerInfo{};
				samplerInfo.sType            = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
				samplerInfo.magFilter        = VK_FILTER_LINEAR;
				samplerInfo.minFilter        = VK_FILTER_LINEAR;
				samplerInfo.addressModeU     = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				samplerInfo.addressModeV     = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				samplerInfo.addressModeW     = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				samplerInfo.anisotropyEnable = VK_TRUE;

				VkPhysicalDeviceProperties properties{};
				vkGetPhysicalDeviceProperties(m_VulkanState.m_PhysicalDevice, &properties);

				samplerInfo.maxAnisotropy           = properties.limits.maxSamplerAnisotropy;
				samplerInfo.borderColor             = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
				samplerInfo.unnormalizedCoordinates = VK_FALSE;
				samplerInfo.compareEnable           = VK_FALSE;
				samplerInfo.compareOp               = VK_COMPARE_OP_ALWAYS;

				samplerInfo.mipmapMode              = VK_SAMPLER_MIPMAP_MODE_LINEAR;
				samplerInfo.mipLodBias              = 0.0f;
				samplerInfo.minLod                  = 0.0f;
				samplerInfo.maxLod                  = static_cast<float>(0);

				VK_CHECK(vkCreateSampler(m_VulkanState.m_Device, &samplerInfo, nullptr, &m_VulkanState.m_SwapChainImageSamplers[i]))
				DEBUGUTILS_SETOBJECTNAME(VK_OBJECT_TYPE_SAMPLER, reinterpret_cast<uint64_t>(m_VulkanState.m_SwapChainImageSamplers[i]), m_VulkanState.m_Device, "SwapChainImageSampler")
			}
		}
    }

}