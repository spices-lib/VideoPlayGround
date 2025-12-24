#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/CommandBuffer.h"
#include <vector>

namespace PlayGround::Vulkan {

	using IGraphicCommandBuffer = InfrastructureClass<class CommandBuffer, EInfrastructure::GraphicCommandBuffer>;
	using IComputeCommandBuffer = InfrastructureClass<class CommandBuffer, EInfrastructure::ComputeCommandBuffer>;

	class CommandBuffer : public Infrastructure
	{
	public:

		CommandBuffer(Context& context, EInfrastructure e, VkCommandPool commandPool, VkCommandBufferLevel level, uint32_t count);

		~CommandBuffer() override = default;

	private:

		void Create(VkCommandPool commandPool, VkCommandBufferLevel level, uint32_t count);

	private:

		std::vector<SP<Unit::CommandBuffer>> m_CommandBuffers;

	};

}