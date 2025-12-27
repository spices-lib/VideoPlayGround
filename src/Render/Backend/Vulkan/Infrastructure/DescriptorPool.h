#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/DescriptorPool.h"
#include <vector>

namespace PlayGround::Vulkan {

	using IDescriptorPool = InfrastructureClass<class DescriptorPool, EInfrastructure::DescriptorPool>;

	class DescriptorPool : public Infrastructure
	{
	public:

		DescriptorPool(Context& context, EInfrastructure e);

		~DescriptorPool() override = default;

		const VkDescriptorPool& Handle() { return m_DescriptorPool.GetHandle(); }

	private:

		void Create();

	private:

		Unit::DescriptorPool m_DescriptorPool;

	};

}