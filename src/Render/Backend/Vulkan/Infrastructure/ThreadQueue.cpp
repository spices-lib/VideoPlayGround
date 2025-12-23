#include "ThreadQueue.h"
#include "DebugUtils.h"
#include <queue>

namespace PlayGround::Vulkan {

    namespace {
    
        std::queue<SP<ThreadQueue>> S_Graphics;
        std::queue<SP<ThreadQueue>> S_Computes;
    }

    ThreadQueue::ThreadQueue(Context& context)
        : Infrastructure(context)
    {}

    void ThreadQueue::AddGraphic(VkQueue handle)
    {
        auto sp = CreateSP<ThreadQueue>(m_Context);
        sp->Init(handle);

        S_Graphics.push(std::move(sp));
    }

    void ThreadQueue::AddCompute(VkQueue handle)
    {
        auto sp = CreateSP<ThreadQueue>(m_Context);
        sp->Init(handle);

        S_Computes.push(std::move(sp));
    }

    void ThreadQueue::Submit(VkCommandBuffer commandBuffer) const
    {
        VkSubmitInfo                     submitInfo{};
		submitInfo.sType               = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount  = 1;
		submitInfo.pCommandBuffers     = &commandBuffer;

		VK_CHECK(vkQueueSubmit(m_Handle, 1, &submitInfo, VK_NULL_HANDLE))
    }

    void ThreadQueue::Wait() const
    {
        VK_CHECK(vkQueueWaitIdle(m_Handle))
    }

    void ThreadQueue::Init(VkQueue handle)
    {
        m_Handle = handle;

        DEBUGUTILS_SETOBJECTNAME(VK_OBJECT_TYPE_QUEUE, reinterpret_cast<uint64_t>(m_Handle), "ThreadQueue")
    }

}