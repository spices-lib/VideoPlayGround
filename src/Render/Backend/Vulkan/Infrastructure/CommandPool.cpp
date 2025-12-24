#include "CommandPool.h"
#include "Device.h"
#include "DebugUtilsObject.h"

namespace PlayGround::Vulkan {

    CommandPool::CommandPool(Context& context, EInfrastructure e, uint32_t family)
        : Infrastructure(context, e)
    {
        Create(family);
    }

    void CommandPool::Create(uint32_t family)
    {
        VkCommandPoolCreateInfo     poolInfo{};
		poolInfo.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.flags            = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		poolInfo.queueFamilyIndex = family;

        m_CommandPool.CreateCommandPool(GetContext().Get<IDevice>()->Handle(), poolInfo);

        DEBUGUTILS_SETOBJECTNAME(m_CommandPool, "CommandPool")
    }

}