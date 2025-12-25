#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/CommandBuffer.h"
#include <vector>

namespace PlayGround::Vulkan {

	using IGraphicCommandBuffer     = InfrastructureClass<class CommandBuffer, EInfrastructure::GraphicCommandBuffer>;
	using IComputeCommandBuffer     = InfrastructureClass<class CommandBuffer, EInfrastructure::ComputeCommandBuffer>;
	using IVideoEncodeCommandBuffer = InfrastructureClass<class CommandBuffer, EInfrastructure::VideoEncodeCommandBuffer>;

	class CommandBuffer : public Infrastructure
	{
	public:

		CommandBuffer(Context& context, EInfrastructure e, VkCommandPool commandPool, VkCommandBufferLevel level, uint32_t count = 1);

		~CommandBuffer() override = default;

		const VkCommandBuffer& Handle(uint32_t index = 0) { return m_CommandBuffers[index]->GetHandle(); }

		void Begin(const VkCommandBufferBeginInfo& info, uint32_t index = 0) const;

		void End(uint32_t index = 0) const;

	private:

		void Create(VkCommandPool commandPool, VkCommandBufferLevel level, uint32_t count);

	private:

		std::vector<SP<Unit::CommandBuffer>> m_CommandBuffers;

	};

}