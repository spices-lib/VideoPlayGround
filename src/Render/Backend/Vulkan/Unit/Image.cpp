#include "Image.h"

namespace PlayGround::Vulkan::Unit {

	Image::~Image()
	{
		if (!m_Handle) return;

		if (auto* p = std::get_if<vkAlloc>(&m_Alloc))
		{
			vkDestroyImage(p->device, m_Handle, nullptr);

			if (p->memory)
			{
				vkFreeMemory(p->device, p->memory, nullptr);
			}
		}
		else if (auto* p = std::get_if<vmaAlloc>(&m_Alloc))
		{
			vmaDestroyImage(p->vma, m_Handle, p->alloc);
		}
		else if (auto* p = std::get_if<std::monostate>(&m_Alloc))
		{
			return;
		}
	}

	void Image::CreateImage(VkPhysicalDevice physicalDevice, VkDevice device, const VkImageCreateInfo& info, VkMemoryPropertyFlags properties)
	{
		assert(device);

		vkAlloc alloc{};
		alloc.device = device;

		VK_CHECK(vkCreateImage(device, &info, nullptr, &m_Handle));

		VkMemoryRequirements memRequirements;
		vkGetImageMemoryRequirements(device, m_Handle, &memRequirements);

		VkMemoryAllocateInfo           allocInfo{};
		allocInfo.sType              = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize     = memRequirements.size;

		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

		allocInfo.memoryTypeIndex = 0;
		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
		{
			if (memRequirements.memoryTypeBits & (1 << i) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
			{
				allocInfo.memoryTypeIndex = i;
			}
		}

		VK_CHECK(vkAllocateMemory(device, &allocInfo, nullptr, &alloc.memory))

		VK_CHECK(vkBindImageMemory(device, m_Handle, alloc.memory, 0))

		m_Alloc = alloc;
	}

	void Image::CreateImage(VmaAllocator vma, const VkImageCreateInfo& info, VmaMemoryUsage usage)
	{
		assert(vma);

		vmaAlloc alloc{};
		alloc.vma = vma;

		VmaAllocationCreateInfo        createInfo{};
		createInfo.usage             = usage;

		VK_CHECK(vmaCreateImage(vma, &info, &createInfo, &m_Handle, &alloc.alloc, nullptr))

		m_Alloc = alloc;
	}

}