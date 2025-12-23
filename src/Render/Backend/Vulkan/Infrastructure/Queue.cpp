#include "Queue.h"
#include "DebugUtils.h"
#include "Queue.h"
#include "Queue.h"

namespace PlayGround::Vulkan {

    Queue::Queue(Context& context)
        : Infrastructure(context)
    {}

    void Queue::Init(VkQueue graphic, VkQueue present, VkQueue compute, VkQueue transfer)
    {
        m_Graphic  = graphic;
        m_Present  = present;
        m_Compute  = compute;
        m_Transfer = transfer;
        
        DEBUGUTILS_SETOBJECTNAME(VK_OBJECT_TYPE_QUEUE, reinterpret_cast<uint64_t>(m_Graphic), "TransferQueue")
        DEBUGUTILS_SETOBJECTNAME(VK_OBJECT_TYPE_QUEUE, reinterpret_cast<uint64_t>(m_Present), "ComputeQueue")
        DEBUGUTILS_SETOBJECTNAME(VK_OBJECT_TYPE_QUEUE, reinterpret_cast<uint64_t>(m_Compute), "PresentQueue")
        DEBUGUTILS_SETOBJECTNAME(VK_OBJECT_TYPE_QUEUE, reinterpret_cast<uint64_t>(m_Transfer), "GraphicQueue")
    }

}