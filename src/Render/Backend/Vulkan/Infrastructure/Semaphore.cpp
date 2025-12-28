#include "Semaphore.h"
#include "Device.h"
#include "DebugUtilsObject.h"
#include <algorithm>

namespace PlayGround::Vulkan {

    Semaphore::Semaphore(Context& context, EInfrastructure e, uint32_t count)
        : Infrastructure(context, e)
    {
        Create(count);
    }

    void Semaphore::SetName(const std::string& name)
    {
        std::ranges::for_each(m_Semaphores, [&](const auto& semphore) {
            DEBUGUTILS_SETOBJECTNAME(*semphore, name)
        });
    }

    void Semaphore::Create(uint32_t count)
    {
        VkSemaphoreCreateInfo semaphoreInfo {};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        for (uint32_t i = 0; i < count; ++i)
        {
            auto semaphore = CreateSP<Unit::Semaphore>();
            semaphore->CreateSemaphore(GetContext().Get<IDevice>()->Handle(), semaphoreInfo);

            m_Semaphores.emplace_back(semaphore);

            DEBUGUTILS_SETOBJECTNAME(*semaphore, "semaphore")
        }
    }

}