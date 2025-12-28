#include "Fence.h"
#include "Device.h"
#include "DebugUtilsObject.h"
#include <algorithm>

namespace PlayGround::Vulkan {

    Fence::Fence(Context& context, EInfrastructure e, uint32_t count)
        : Infrastructure(context, e)
    {
        Create(count);
    }

    void Fence::Create(uint32_t count)
    {
        VkFenceCreateInfo fenceInfo {};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (uint32_t i = 0; i < count; ++i)
        {
            auto fence = CreateSP<Unit::Fence>();
            fence->CreateFence(GetContext().Get<IDevice>()->Handle(), fenceInfo);
 
            m_Fences.emplace_back(fence);

            DEBUGUTILS_SETOBJECTNAME(*fence, "Fence")
        }
    }

    void Fence::SetName(const std::string& name)
    {
        std::ranges::for_each(m_Fences, [&](const auto& fence) {
            DEBUGUTILS_SETOBJECTNAME(*fence, name)
        });
    }

    void Fence::Wait(uint32_t index)
    {
        auto& fence = m_Fences[index];

        fence->WaitFence();

        fence->ResetFence();
    }

    void Fence::WaitAll()
    {
        std::ranges::for_each(m_Fences, [](const auto& fence) {
            fence->WaitFence();
            fence->ResetFence();
        });
    }

}