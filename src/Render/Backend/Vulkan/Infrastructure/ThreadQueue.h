#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/Queue.h"
#include <vector>

namespace PlayGround::Vulkan {

	using IGraphicThreadQueue = InfrastructureClass<class ThreadQueue, EInfrastructure::GraphicThreadQueue>;
	using IComputeThreadQueue = InfrastructureClass<class ThreadQueue, EInfrastructure::ComputeThreadQueue>;

	class ThreadQueue : public Infrastructure
	{
	public:

		ThreadQueue(Context& context, EInfrastructure e);

		~ThreadQueue() override = default;

		void Add(VkQueue handle);

		void SetName(const std::string& name);

	private:

		std::vector<SP<Unit::Queue>> m_Queues;

	};
	
}