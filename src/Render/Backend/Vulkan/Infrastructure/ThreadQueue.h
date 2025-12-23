#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"

namespace PlayGround::Vulkan {

	class ThreadQueue : public Infrastructure
	{
	public:

		static constexpr EInfrastructure Type = EInfrastructure::ThreadQueue;

	public:

		ThreadQueue(Context& context);

		~ThreadQueue() override = default;

		void AddGraphic(VkQueue handle);
		void AddCompute(VkQueue handle);

	public:

		void Submit(VkCommandBuffer commandBuffer) const;

		void Wait() const;

	private:

		void Init(VkQueue handle);

	private:

		VkQueue m_Handle = nullptr;

	};

	template<>
	inline void Infrastructure::Destroy(ThreadQueue* infrastructure)
	{}

}