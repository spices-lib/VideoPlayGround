#include "Queue.h"
#include "CommandBuffer.h"
#include <algorithm>

namespace PlayGround::Vulkan::Unit {

	void Queue::Submit(CommandBuffer commandBuffer) const
	{
		VkSubmitInfo                     submitInfo{};
		submitInfo.sType               = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount  = 1;
		submitInfo.pCommandBuffers     = &commandBuffer.GetHandle();

		VK_CHECK(vkQueueSubmit(m_Handle, 1, &submitInfo, VK_NULL_HANDLE))
	}

	void Queue::Submit(const std::vector<CommandBuffer>& commandBuffers) const
	{
		std::vector<VkCommandBuffer> handles;

		std::for_each(commandBuffers.begin(), commandBuffers.end(), [&](const auto& commandBuffer) {
			handles.emplace_back(commandBuffer.GetHandle());
		});

		VkSubmitInfo                     submitInfo{};
		submitInfo.sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount   = handles.size();
		submitInfo.pCommandBuffers      = handles.data();

		VK_CHECK(vkQueueSubmit(m_Handle, 1, &submitInfo, VK_NULL_HANDLE))
	}

	void Queue::Wait() const
	{
		VK_CHECK(vkQueueWaitIdle(m_Handle))
	}
}