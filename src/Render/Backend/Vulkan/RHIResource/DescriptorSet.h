#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/DescriptorSet.h"
#include "Render/Backend/Vulkan/Unit/DescriptorSetLayout.h"
#include "Render/Backend/Vulkan/Unit/Buffer.h"
#include <map>
#include <vector>

namespace PlayGround::Vulkan {

	class DescriptorSet : public ContextAccessor
	{
	public:

		DescriptorSet(Context& context) : ContextAccessor(context) {}
		~DescriptorSet() override = default;

		void AddBinding(const VkBufferCreateInfo& info, const VkDescriptorSetLayoutBinding& binding);

		void BuildDescriptorSet();

		void UpdateDescriptorSet();

	private:

		void CreateDescriptorSetLayout();

	private:

		struct BufferBindingData {
			SP<Unit::Buffer> buffer;
			VkDescriptorBufferInfo bufferInfo;
		};

		struct ImageBindingData {
			std::vector<VkDescriptorImageInfo> imageInfos;
		};

		struct BindingData {
			VkDescriptorSetLayoutBinding  binding;
			std::variant<BufferBindingData, ImageBindingData> data;
		};

		Unit::DescriptorSet                       m_DescriptorSet;
		Unit::DescriptorSetLayout                 m_Layout;
		std::map<uint32_t, BindingData>           m_Bindings;
	};
}