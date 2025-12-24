#include "ThreadQueue.h"
#include "DebugUtilsObject.h"
#include <queue>

namespace PlayGround::Vulkan {

    ThreadQueue::ThreadQueue(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {}

    void ThreadQueue::Add(VkQueue handle)
    {
        auto q = Unit::Queue();
        q.SetHandle(handle);

        DEBUGUTILS_SETOBJECTNAME(q, "ThreadQueue")

        m_Queues.emplace(std::move(q));
    }

}