#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/Fence.h"
#include <vector>

namespace PlayGround::Vulkan {

	using IGraphicFence     = InfrastructureClass<class Fence, EInfrastructure::GraphicFence>;
	using IComputeFence     = InfrastructureClass<class Fence, EInfrastructure::ComputeFence>;
	using IVideoEncodeFence = InfrastructureClass<class Fence, EInfrastructure::VideoEncodeFence>;

	class Fence : public Infrastructure
	{
	public:

		Fence(Context& context, EInfrastructure e, uint32_t count = 1);

		~Fence() override = default;

		const VkFence& Handle(uint32_t index = 0) { return m_Fences[index]->GetHandle(); }

		void Wait(uint32_t index);
		void WaitAll();

	private:

		void Create(uint32_t count);

	private:

		std::vector<SP<Unit::Fence>> m_Fences;

	};
	
}