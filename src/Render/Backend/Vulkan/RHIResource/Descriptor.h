#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/DescriptorSet.h"
#include "Render/Frontend/RHI/Descriptor.h"

namespace PlayGround::Vulkan {

	class Descriptor : public ContextAccessor, public RHI::Descriptor::Impl
	{
	public:

		Descriptor(Context& context) : ContextAccessor(context), RHI::Descriptor::Impl() {}
		~Descriptor() override = default;

		void Build() override;

	private:

		Unit::DescriptorSet m_DescriptorSet;
	};
}