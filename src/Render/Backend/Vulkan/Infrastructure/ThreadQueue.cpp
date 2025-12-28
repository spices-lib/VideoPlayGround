#include "ThreadQueue.h"
#include "DebugUtilsObject.h"
#include <queue>
#include <algorithm>

namespace PlayGround::Vulkan {

    ThreadQueue::ThreadQueue(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {}

    void ThreadQueue::Add(VkQueue handle)
    {
        auto queue = CreateSP<Unit::Queue>();
        queue->SetHandle(handle);

        m_Queues.emplace_back(queue);

        DEBUGUTILS_SETOBJECTNAME(*queue, "ThreadQueue")
    }

    void ThreadQueue::SetName(const std::string& name)
    {
        std::ranges::for_each(m_Queues, [&](const auto& queue) {
            DEBUGUTILS_SETOBJECTNAME(*queue, name)
        });
    }

}