#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/CommandPool.h"

namespace PlayGround::Vulkan {

	using IGraphicCommandPool = InfrastructureClass<class CommandPool, EInfrastructure::GraphicCommandPool>;
	using IComputeCommandPool = InfrastructureClass<class CommandPool, EInfrastructure::ComputeCommandPool>;

	class CommandPool : public Infrastructure
	{
	public:

		CommandPool(Context& context, EInfrastructure e, uint32_t family);

		~CommandPool() override = default;

		const VkCommandPool& Handle() { return m_CommandPool.GetHandle(); }

	private:

		void Create(uint32_t family);

	private:

		Unit::CommandPool m_CommandPool;

	};

}