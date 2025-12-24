#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class CommandBuffer : public Unit<VkCommandBuffer, VkObjectType::VK_OBJECT_TYPE_COMMAND_BUFFER>
	{
	public:

		using Handle = Unit::Handle;

	public:

		CommandBuffer() : Unit() {}

		~CommandBuffer() override;

		void CreateCommandBuffer(VkDevice device, const VkCommandBufferAllocateInfo& info);

		void Begin(const VkCommandBufferBeginInfo& info);

		void End();

	private:

		VkDevice m_Device = VK_NULL_HANDLE;
		VkCommandPool m_CommandPool = VK_NULL_HANDLE;
	};
}