#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/RHIResource/DescriptorSet.h"
#include "Render/Backend/Vulkan/Unit/Buffer.h"
#include "Render/Frontend/RHI/DescriptorList.h"
#include <map>

namespace PlayGround::Vulkan {

	class DescriptorList : public ContextAccessor, public RHI::DescriptorList::Impl
	{
	public:

		DescriptorList(Context& context) : ContextAccessor(context), RHI::DescriptorList::Impl() {}
		~DescriptorList() override = default;

		void AddUniformBuffer(uint32_t set, uint32_t binding, uint32_t bytes) override;

		void Build() override;

	private:

		SP<DescriptorSet> AccessSet(uint32_t set);

	private:

		std::map<uint32_t, SP<DescriptorSet>> m_DescriptorSets;

	};
}