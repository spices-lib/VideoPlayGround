#include "CommandBuffer.h"
#include "Device.h"
#include "DebugUtilsObject.h"
#include <algorithm>

namespace PlayGround::Vulkan {

    CommandBuffer::CommandBuffer(Context& context, EInfrastructure e, VkCommandPool commandPool, VkCommandBufferLevel level, uint32_t count)
        : Infrastructure(context, e)
    {
        Create(commandPool, level, count);
    }

    void CommandBuffer::Create(VkCommandPool commandPool, VkCommandBufferLevel level, uint32_t count)
    {
        VkCommandBufferAllocateInfo       allocInfo{};
		allocInfo.sType                 = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool           = commandPool;
		allocInfo.level                 = level;
		allocInfo.commandBufferCount    = 1;

        for (uint32_t i = 0; i < count; ++i)
        {
            auto commandBuffer = CreateSP<Unit::CommandBuffer>();
            commandBuffer->CreateCommandBuffer(GetContext().Get<IDevice>()->Handle(), allocInfo);

            m_CommandBuffers.emplace_back(commandBuffer);

            DEBUGUTILS_SETOBJECTNAME(*commandBuffer, "CommandBuffer")
        }
    }

    void CommandBuffer::Begin(const VkCommandBufferBeginInfo& info, uint32_t index) const
    {
        m_CommandBuffers[index]->Begin(info);
    }

    void CommandBuffer::End(uint32_t index) const
    {
        m_CommandBuffers[index]->End();
    }

    void CommandBuffer::SetName(const std::string& name)
    {
        std::ranges::for_each(m_CommandBuffers, [&](const auto& commandBuffer) {
            DEBUGUTILS_SETOBJECTNAME(*commandBuffer, name)
        });
    }
}
