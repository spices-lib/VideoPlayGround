#include "Converter.h"

namespace PlayGround::Vulkan {

	VkFormat ToVkFormat(TextureFormat f)
	{
		switch (f)
		{
		case TextureFormat::RGBA8_UNORM:   return VkFormat::VK_FORMAT_R8G8B8A8_UNORM;
		case TextureFormat::RGBA16_SFLOAT: return VkFormat::VK_FORMAT_R16G16B16A16_SFLOAT;
		default:
		{
			CORE_WARN("Unsupported Texture Format To VkFormat.")
			return VK_FORMAT_R8G8B8A8_UNORM;
		}
		}
	}

	VkImageType ToVkImageType(TextureDomain d)
	{
		switch (d)
		{
		case TextureDomain::Texture1D:      return VkImageType::VK_IMAGE_TYPE_1D;
		case TextureDomain::Texture1DArray: return VkImageType::VK_IMAGE_TYPE_1D;
		case TextureDomain::Texture2D:      return VkImageType::VK_IMAGE_TYPE_2D;
		case TextureDomain::Texture2DArray: return VkImageType::VK_IMAGE_TYPE_2D;
		case TextureDomain::Texture3D:      return VkImageType::VK_IMAGE_TYPE_3D;
		default:
		{
			CORE_WARN("Unsupported Texture Domain To VkImageType.")
			return VK_IMAGE_TYPE_1D;
		}
		}
	}

	VkImageViewType ToVkImageViewType(TextureDomain d)
	{
		switch (d)
		{
		case TextureDomain::Texture1D:      return VkImageViewType::VK_IMAGE_VIEW_TYPE_1D;
		case TextureDomain::Texture1DArray: return VkImageViewType::VK_IMAGE_VIEW_TYPE_1D_ARRAY;
		case TextureDomain::Texture2D:      return VkImageViewType::VK_IMAGE_VIEW_TYPE_2D;
		case TextureDomain::Texture2DArray: return VkImageViewType::VK_IMAGE_VIEW_TYPE_2D_ARRAY;
		case TextureDomain::Texture3D:      return VkImageViewType::VK_IMAGE_VIEW_TYPE_3D;
		default:
		{
			CORE_WARN("Unsupported Texture Domain To VkImageViewType.")
			return VK_IMAGE_VIEW_TYPE_2D;
		}
		}
	}

	VkMemoryPropertyFlags ToVkMemoryPropertyFlags(RHIMemoryUsage u)
	{
		switch (u)
		{
		case RHIMemoryUsage::Device:    return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
		case RHIMemoryUsage::Host:      return VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
		case RHIMemoryUsage::Shared:    return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
		case RHIMemoryUsage::Preserved: return VK_MEMORY_PROPERTY_PROTECTED_BIT;
		default:
		{
			CORE_WARN("Unsupported RHIMemoryUsage To VkMemoryPropertyFlags.")
			return VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
		}
		}
	}

	VmaMemoryUsage ToVmaMemoryUsage(RHIMemoryUsage u)
	{
		switch (u)
		{
		case RHIMemoryUsage::Device:    return VMA_MEMORY_USAGE_GPU_ONLY;
		case RHIMemoryUsage::Host:      return VMA_MEMORY_USAGE_CPU_ONLY;
		case RHIMemoryUsage::Shared:    return VMA_MEMORY_USAGE_CPU_TO_GPU;
		default:
		{
			CORE_WARN("Unsupported RHIMemoryUsage To VmaMemoryUsage.")
			return VMA_MEMORY_USAGE_GPU_ONLY;
		}
		}
	}

	VkCullModeFlags ToVkCullModeFlags(CullMode c)
	{
		switch (c)
		{
		case CullMode::None:    return VK_CULL_MODE_NONE;
		case CullMode::Front:   return VK_CULL_MODE_FRONT_BIT;
		case CullMode::Back:    return VK_CULL_MODE_BACK_BIT;
		default:
		{
			CORE_WARN("Unsupported CullMode To VkCullModeFlags.")
			return VK_CULL_MODE_NONE;
		}
		}
	}
}