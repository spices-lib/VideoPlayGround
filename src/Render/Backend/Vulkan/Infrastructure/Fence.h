#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/Fence.h"

namespace PlayGround::Vulkan {

	using IGraphicFence = InfrastructureClass<class Fence, EInfrastructure::GraphicFence>;
	using IComputeFence = InfrastructureClass<class Fence, EInfrastructure::ComputeFence>;

	class Fence : public Infrastructure
	{
	public:

		Fence(Context& context, EInfrastructure e);

		~Fence() override = default;

		const VkFence& Handle() { return m_Fence.GetHandle(); }

	private:

		void Create();

	private:

		Unit::Fence m_Fence;

	};
	
}