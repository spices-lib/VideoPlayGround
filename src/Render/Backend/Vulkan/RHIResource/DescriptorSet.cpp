#include "DescriptorSet.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Render/Backend/Vulkan/Infrastructure/MemoryAllocator.h"
#include "Render/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Render/Backend/Vulkan/Infrastructure/DescriptorPool.h"
#include <ranges>

namespace PlayGround::Vulkan {

	void DescriptorSet::AddBinding(const VkBufferCreateInfo& info, const VkDescriptorSetLayoutBinding& binding)
	{
		auto buffer = CreateSP<Unit::Buffer>();
		
		if (GetContext().Has<IMemoryAllocator>())
		{
			buffer->CreateBuffer(
				GetContext().Get<IMemoryAllocator>()->Handle(),
				GetContext().Get<IDevice>()->Handle(),
				info,
				VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
			);
		}
		else
		{
			buffer->CreateBuffer(
				GetContext().Get<IPhysicalDevice>()->Handle(),
				GetContext().Get<IDevice>()->Handle(),
				info,
				VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
			);
		}

		BufferBindingData data{};
		data.buffer = buffer;

		m_Bindings.emplace(binding.binding, BindingData{ binding, data });
	}

	void DescriptorSet::BuildDescriptorSet()
	{
		CreateDescriptorSetLayout();

		VkDescriptorSetAllocateInfo        allocInfo{};
		allocInfo.sType                  = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocInfo.descriptorPool         = GetContext().Get<IDescriptorPool>()->Handle();
		allocInfo.pSetLayouts            = &m_Layout.GetHandle();
		allocInfo.descriptorSetCount     = 1;

		m_DescriptorSet.AllocateDescriptorSet(GetContext().Get<IDevice>()->Handle(), allocInfo);
	}

	void DescriptorSet::UpdateDescriptorSet()
	{
		for (int i = 0; i < m_Bindings.size(); ++i)
		{
			const auto& binding = m_Bindings[i];

			VkWriteDescriptorSet              write{};
			write.sType                     = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			write.dstBinding                = i;
			write.dstSet                    = m_DescriptorSet.GetHandle();
			write.descriptorType            = binding.binding.descriptorType;

			switch (write.descriptorType)
			{
			case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
			case VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
			case VK_DESCRIPTOR_TYPE_STORAGE_IMAGE:
			{
				auto& imageInfos            = std::get<ImageBindingData>(binding.data).imageInfos;
				write.pImageInfo            = imageInfos.data();
				write.descriptorCount       = imageInfos.size();
				break;
			}
			case VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
			case VK_DESCRIPTOR_TYPE_STORAGE_BUFFER:
				write.pBufferInfo           = &std::get<BufferBindingData>(binding.data).bufferInfo;
				write.descriptorCount       = 1;
				break;
			}

			m_DescriptorSet.UpdateDescriptorSet(write);
		}
	}

	void DescriptorSet::CreateDescriptorSetLayout()
	{
		std::vector<VkDescriptorSetLayoutBinding> setBindings{};
		std::vector<VkDescriptorBindingFlags> setBindingFlags{};

		for (auto& data : m_Bindings | std::views::values)
		{
			setBindings.emplace_back(data.binding);

			switch (data.binding.descriptorType)
			{
			case VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
				setBindingFlags.emplace_back(VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT);
				break;
			default:
				setBindingFlags.emplace_back(VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT | VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT);
				break;
			}
		}

		VkDescriptorSetLayoutBindingFlagsCreateInfo         bindingFlags{};
		bindingFlags.sType                                = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO;
		bindingFlags.pNext                                = nullptr;
		bindingFlags.pBindingFlags                        = setBindingFlags.data();
		bindingFlags.bindingCount                         = setBindingFlags.size();

		VkDescriptorSetLayoutCreateInfo                     layoutCreateInfo{};
		layoutCreateInfo.sType                            = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		layoutCreateInfo.bindingCount                     = setBindings.size();
		layoutCreateInfo.pBindings                        = setBindings.data();
		layoutCreateInfo.flags                            = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT;
		layoutCreateInfo.pNext                            = &bindingFlags;

		m_Layout.CreateDescriptorSetLayout(GetContext().Get<IDevice>()->Handle(), layoutCreateInfo);
	}
}