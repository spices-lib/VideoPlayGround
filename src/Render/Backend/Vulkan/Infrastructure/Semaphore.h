#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/Semaphore.h"
#include <vector>

namespace PlayGround::Vulkan {

	using IGraphicImageSemaphore     = InfrastructureClass<class Semaphore, EInfrastructure::GraphicImageSemaphore>;
	using IGraphicQueueSemaphore     = InfrastructureClass<class Semaphore, EInfrastructure::GraphicQueueSemaphore>;
	using IComputeQueueSemaphore     = InfrastructureClass<class Semaphore, EInfrastructure::ComputeQueueSemaphore>;
	using IVideoEncodeQueueSemaphore = InfrastructureClass<class Semaphore, EInfrastructure::VideoEncodeQueueSemaphore>;

	class Semaphore : public Infrastructure
	{
	public:

		Semaphore(Context& context, EInfrastructure e, uint32_t count = 1);

		~Semaphore() override = default;

		const VkSemaphore& Handle(uint32_t index = 0) { return m_Semaphores[index]->GetHandle(); }

	private:

		void Create(uint32_t count);

	private:

		std::vector<SP<Unit::Semaphore>> m_Semaphores;

	};

}