#include "Semaphore.h"
#include "Device.h"
#include "DebugUtilsObject.h"

namespace PlayGround::Vulkan {

    Semaphore::Semaphore(Context& context, EInfrastructure e, uint32_t count)
        : Infrastructure(context, e)
    {
        Create(count);
    }

    void Semaphore::Create(uint32_t count)
    {
        VkSemaphoreCreateInfo semaphoreInfo {};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        for (uint32_t i = 0; i < count; ++i)
        {
            auto semphore = CreateSP<Unit::Semaphore>();
            semphore->CreateSemaphore(GetContext().Get<IDevice>()->Handle(), semaphoreInfo);

            m_Semaphores.emplace_back(semphore);

            DEBUGUTILS_SETOBJECTNAME(*semphore, "Semaphore")
        }
    }

}