#include "Queue.h"
#include "DebugUtilsObject.h"
#include "Queue.h"
#include "Queue.h"

namespace PlayGround::Vulkan {

    Queue::Queue(Context& context, EInfrastructure e, VkQueue queue)
        : Infrastructure(context, e)
    {
        Init(queue);
    }

    void Queue::Init(VkQueue queue)
    {
        m_Queue.SetHandle(queue);
        
        DEBUGUTILS_SETOBJECTNAME(m_Queue, "Queue")
    }

    void Queue::Submit(const VkSubmitInfo& info, VkFence fence)
    {
        m_Queue.Submit(info, fence);
    }

    void Queue::Wait()
    {
        m_Queue.Wait();
    }
}