#pragma once
#include "Core/Core.h"
#include "Unit.h"
#include <vk_mem_alloc.h>
#include <variant>

namespace PlayGround::Vulkan::Unit {

	class Buffer : public Unit<VkBuffer, VkObjectType::VK_OBJECT_TYPE_BUFFER>
	{
	public:

		using Handle = Unit::Handle;

	public:

		Buffer() : Unit() {}

		~Buffer() override;

		void CreateBuffer(VkPhysicalDevice physicalDevice, VkDevice device, const VkBufferCreateInfo& info, VkMemoryPropertyFlags properties);

		void CreateBuffer(VmaAllocator vma, VkDevice device, const VkBufferCreateInfo& info, VkMemoryPropertyFlags properties);

	private:

		struct vkAlloc {
			VkDevice         device     = VK_NULL_HANDLE;
			VkDeviceMemory   memory     = VK_NULL_HANDLE;
			void*            hostMemory = nullptr;
		};

		struct vmaAlloc {
			VmaAllocator   vma  = VK_NULL_HANDLE;
			VmaAllocation  alloc = VK_NULL_HANDLE;
		};

		std::variant<std::monostate, vkAlloc, vmaAlloc> m_Alloc{ std::monostate{} };
		VkDeviceAddress  m_Address;
	};
}