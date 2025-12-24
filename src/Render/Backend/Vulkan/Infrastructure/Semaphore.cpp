#include "Semaphore.h"
#include "Device.h"
#include "DebugUtilsObject.h"

namespace PlayGround::Vulkan {

    Semaphore::Semaphore(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        Create();
    }

    void Semaphore::Create()
    {
        VkSemaphoreCreateInfo semaphoreInfo {};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        m_Semaphore.CreateSemaphore(GetContext().Get<IDevice>()->Handle(), semaphoreInfo);

        DEBUGUTILS_SETOBJECTNAME(m_Semaphore, "Semaphore")
    }

}