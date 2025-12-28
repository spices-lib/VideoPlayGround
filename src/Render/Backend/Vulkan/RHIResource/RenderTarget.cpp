#include "RenderTarget.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Render/Backend/Vulkan/Infrastructure/MemoryAllocator.h"
#include "Render/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Resource/Texture/RenderTarget.h"
#include "Render/Backend/Vulkan/Converter.h"

namespace PlayGround::Vulkan {

	void RenderTarget::CreateRenderTarget(RenderTargetCreateInfo& info)
	{
		{
			VkImageCreateInfo                                  createInfo{};
			createInfo.sType                                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
			createInfo.imageType                             = ToVkImageType(info.domain);
			createInfo.extent.width                          = info.width;
			createInfo.extent.height                         = info.height;
			createInfo.extent.depth                          = 1;
			createInfo.mipLevels                             = 1;
			createInfo.arrayLayers                           = 1;
			createInfo.format                                = ToVkFormat(info.format);
			createInfo.tiling                                = VK_IMAGE_TILING_OPTIMAL;
			createInfo.initialLayout                         = VK_IMAGE_LAYOUT_UNDEFINED;
			createInfo.usage                                 = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | 
														       VK_IMAGE_USAGE_SAMPLED_BIT;
			createInfo.sharingMode                           = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.samples                               = VK_SAMPLE_COUNT_1_BIT;
			createInfo.flags                                 = 0;

			m_Image.CreateImage(createInfo, GetContext().Has<IMemoryAllocator>() ? ToVmaMemoryUsage(info.memoryUsage) : ToVkMemoryPropertyFlags(info.memoryUsage));
		}

		{
			VkImageViewCreateInfo                              createInfo{};
			createInfo.sType                                 = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
							                                
			createInfo.viewType                              = ToVkImageViewType(info.domain);
			createInfo.format                                = ToVkFormat(info.format);
												       	  
			createInfo.components.r                          = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g                          = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b                          = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a                          = VK_COMPONENT_SWIZZLE_IDENTITY;
												       	  
			createInfo.subresourceRange.aspectMask           = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel         = 0;
			createInfo.subresourceRange.levelCount           = 1;
			createInfo.subresourceRange.baseArrayLayer       = 0;
			createInfo.subresourceRange.layerCount           = 1;

			m_Image.CreateImageView(createInfo);
		}

		{
			VkSamplerCreateInfo                                createInfo{};
			createInfo.sType                                 = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
			createInfo.magFilter                             = VK_FILTER_LINEAR;
			createInfo.minFilter                             = VK_FILTER_LINEAR;
			createInfo.addressModeU                          = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			createInfo.addressModeV                          = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			createInfo.addressModeW                          = VK_SAMPLER_ADDRESS_MODE_REPEAT;
			createInfo.anisotropyEnable                      = VK_TRUE;

			VkPhysicalDeviceProperties                         properties{};
			vkGetPhysicalDeviceProperties(GetContext().Get<IPhysicalDevice>()->Handle(), &properties);

			createInfo.maxAnisotropy                         = properties.limits.maxSamplerAnisotropy;
			createInfo.borderColor                           = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
			createInfo.unnormalizedCoordinates               = VK_FALSE;
			createInfo.compareEnable                         = VK_FALSE;
			createInfo.compareOp                             = VK_COMPARE_OP_ALWAYS;
													         
			createInfo.mipmapMode                            = VK_SAMPLER_MIPMAP_MODE_LINEAR;
			createInfo.mipLodBias                            = 0.0f;
			createInfo.minLod                                = 0;
			createInfo.maxLod                                = 1;

			m_Image.CreateSampler(createInfo);
		}

		m_Image.SetName(info.name);
	}

	const VkImageView& RenderTarget::GetView() const
	{
		return m_Image.GetView();
	}
}