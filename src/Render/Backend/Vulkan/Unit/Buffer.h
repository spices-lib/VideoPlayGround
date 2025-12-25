#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class Buffer : public Unit<VkBuffer, VkObjectType::VK_OBJECT_TYPE_BUFFER>
	{
	public:

		using Handle = Unit::Handle;

	public:

		Buffer() : Unit() {}

		~Buffer() override;

		void CreateBuffer(VkDevice device, const VkBufferCreateInfo& info);

	private:

		VkDevice         m_Device = VK_NULL_HANDLE;
		VkDeviceMemory   m_Memory = VK_NULL_HANDLE;
	};
}