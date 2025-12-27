#include "DescriptorPool.h"
#include "Device.h"
#include "DebugUtilsObject.h"

namespace PlayGround::Vulkan {

    DescriptorPool::DescriptorPool(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        Create();
    }

    void DescriptorPool::Create()
    {
        std::vector<VkDescriptorPoolSize> poolSizes{};

        {
            VkDescriptorPoolSize             poolSize{};
            poolSize.type                  = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            poolSize.descriptorCount       = 1000;

            poolSizes.emplace_back(poolSize);
        }

        {
            VkDescriptorPoolSize             poolSize{};
            poolSize.type                  = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
            poolSize.descriptorCount       = 1000;

            poolSizes.emplace_back(poolSize);
        }

        {
            VkDescriptorPoolSize             poolSize{};
            poolSize.type                  = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            poolSize.descriptorCount       = 1000; 

            poolSizes.emplace_back(poolSize);
        }

        {
            VkDescriptorPoolSize             poolSize{};
            poolSize.type                  = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
            poolSize.descriptorCount       = 1000; 

            poolSizes.emplace_back(poolSize);
        }

        {
            VkDescriptorPoolSize             poolSize{};
            poolSize.type                  = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
            poolSize.descriptorCount       = 1000;

            poolSizes.emplace_back(poolSize);
        }

        VkDescriptorPoolCreateInfo           createInfo{};
		createInfo.sType                   = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		createInfo.poolSizeCount           = static_cast<uint32_t>(poolSizes.size());
		createInfo.pPoolSizes              = poolSizes.data();
		createInfo.maxSets                 = 1000;
		createInfo.flags                   = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT | VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT;;

        m_DescriptorPool.CreateDescriptorPool(GetContext().Get<IDevice>()->Handle(), createInfo);

        DEBUGUTILS_SETOBJECTNAME(m_DescriptorPool, "DescriptorPool")
    }

}