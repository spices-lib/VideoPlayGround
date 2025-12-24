#include "Queue.h"
#include "CommandBuffer.h"
#include <algorithm>

namespace PlayGround::Vulkan::Unit {

	void Queue::Submit(const VkSubmitInfo& info, VkFence fence) const
	{
		VK_CHECK(vkQueueSubmit(m_Handle, 1, &info, fence))
	}

	void Queue::Wait() const
	{
		VK_CHECK(vkQueueWaitIdle(m_Handle))
	}
}