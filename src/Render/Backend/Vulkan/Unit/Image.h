#pragma once
#include "Core/Core.h"
#include "Unit.h"
#include <vk_mem_alloc.h>
#include <variant>

namespace PlayGround::Vulkan::Unit {

	class Image : public Unit<VkImage, VkObjectType::VK_OBJECT_TYPE_IMAGE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		Image() : Unit() {}

		~Image() override;

		void CreateImage(VkPhysicalDevice physicalDevice, VkDevice device, const VkImageCreateInfo& info, VkMemoryPropertyFlags properties);

		void CreateImage(VmaAllocator vma, const VkImageCreateInfo& info, VkMemoryPropertyFlags properties);

	private:

		struct vkAlloc {
			VkDevice       device = VK_NULL_HANDLE;
			VkDeviceMemory memory = VK_NULL_HANDLE;
		};

		struct vmaAlloc {
			VmaAllocator   vma    = VK_NULL_HANDLE;
			VmaAllocation  alloc  = VK_NULL_HANDLE;
		};

		std::variant<std::monostate, vkAlloc, vmaAlloc> m_Alloc{ std::monostate{} };
	};
}