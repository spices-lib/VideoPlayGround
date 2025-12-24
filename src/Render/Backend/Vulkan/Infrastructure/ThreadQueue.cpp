#include "ThreadQueue.h"
#include "DebugUtilsObject.h"
#include <queue>

namespace PlayGround::Vulkan {

    ThreadQueue::ThreadQueue(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {}

    void ThreadQueue::Add(VkQueue handle)
    {
        auto queue = CreateSP<Unit::Queue>();
        queue->SetHandle(handle);

        m_Queues.emplace(queue);

        DEBUGUTILS_SETOBJECTNAME(*queue, "ThreadQueue")
    }

}