#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/Semaphore.h"

namespace PlayGround::Vulkan {

	using IGraphicImageSemaphore = InfrastructureClass<class Semaphore, EInfrastructure::GraphicImageSemaphore>;
	using IGraphicQueueSemaphore = InfrastructureClass<class Semaphore, EInfrastructure::GraphicQueueSemaphore>;
	using IComputeQueueSemaphore = InfrastructureClass<class Semaphore, EInfrastructure::ComputeQueueSemaphore>;

	class Semaphore : public Infrastructure
	{
	public:

		Semaphore(Context& context, EInfrastructure e);

		~Semaphore() override = default;

		const VkSemaphore& Handle() { return m_Semaphore.GetHandle(); }

	private:

		void Create();

	private:

		Unit::Semaphore m_Semaphore;

	};

}