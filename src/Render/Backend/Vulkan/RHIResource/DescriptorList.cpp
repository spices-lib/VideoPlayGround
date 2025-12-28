#include "DescriptorList.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Render/Backend/Vulkan/Infrastructure/MemoryAllocator.h"
#include "Render/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include <vma/vk_mem_alloc.h>
#include <algorithm>

namespace PlayGround::Vulkan {

	void DescriptorList::AddUniformBuffer(uint32_t set, uint32_t binding, uint32_t bytes)
	{
		auto descriptorSet = AccessSet(set);

		VkBufferCreateInfo                    info{};
		info.sType                          = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		info.size                           = bytes;
		info.usage                          = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
		info.sharingMode                    = VK_SHARING_MODE_EXCLUSIVE;

		VkDescriptorSetLayoutBinding          layoutBinding{};
		layoutBinding.binding               = binding;
		layoutBinding.descriptorType        = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		layoutBinding.descriptorCount       = 1;
		layoutBinding.stageFlags            = VK_SHADER_STAGE_ALL;

		descriptorSet->AddBinding(info, layoutBinding);
	}

	void DescriptorList::Build()
	{
		std::ranges::for_each(m_DescriptorSets.begin(), m_DescriptorSets.end(), [](const auto& pair) {
			
			pair.second->BuildDescriptorSet();

			pair.second->UpdateDescriptorSet();
		});
	}

	SP<DescriptorSet> DescriptorList::AccessSet(uint32_t set)
	{
		if (!m_DescriptorSets.contains(set))
		{
			m_DescriptorSets[set] = CreateSP<DescriptorSet>(GetContext());
		}
		
		return m_DescriptorSets.at(set);
	}
	
}
