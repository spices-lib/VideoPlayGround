#pragma once
#include "Core.h"
#include "Resource/Texture/RenderTarget.h"
#include "Resource/Mesh/Mesh.h"
#include <vk_mem_alloc.h>

namespace PlayGround::Vulkan {

	VkFormat ToVkFormat(TextureFormat f);

	VkImageType ToVkImageType(TextureDomain d);

	VkImageViewType ToVkImageViewType(TextureDomain d);

	VkMemoryPropertyFlags ToVkMemoryPropertyFlags(RHIMemoryUsage u);

	VmaMemoryUsage ToVmaMemoryUsage(RHIMemoryUsage u);

	VkCullModeFlags ToVkCullModeFlags(CullMode c);
}