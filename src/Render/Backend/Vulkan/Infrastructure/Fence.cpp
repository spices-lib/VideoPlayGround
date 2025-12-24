#include "Fence.h"
#include "Device.h"
#include "DebugUtilsObject.h"

namespace PlayGround::Vulkan {

    Fence::Fence(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        Create();
    }

    void Fence::Create()
    {
        VkFenceCreateInfo fenceInfo {};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        m_Fence.CreateFence(GetContext().Get<IDevice>()->Handle(), fenceInfo);

        DEBUGUTILS_SETOBJECTNAME(m_Fence, "Fence")
    }

}