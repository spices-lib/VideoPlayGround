#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"

namespace PlayGround::Vulkan {

	class Queue : public Infrastructure
	{
	public:

		static constexpr EInfrastructure Type = EInfrastructure::Queue;

	public:

		Queue(Context& context);

		~Queue() override = default;

		void Init(VkQueue graphic, VkQueue present, VkQueue compute, VkQueue transfer);

		VkQueue& Graphic()  { return m_Graphic; }
		VkQueue& Present()  { return m_Present; }
		VkQueue& Compute()  { return m_Compute; }
		VkQueue& Transfer() { return m_Transfer; }

	private:

		VkQueue m_Graphic  = nullptr;
		VkQueue m_Present  = nullptr;
		VkQueue m_Compute  = nullptr;
		VkQueue m_Transfer = nullptr;
	};

	template<>
	inline void Infrastructure::Destroy(Queue* infrastructure)
	{
		infrastructure->Graphic()  = nullptr;
		infrastructure->Present()  = nullptr;
		infrastructure->Compute()  = nullptr;
		infrastructure->Transfer() = nullptr;
	}

}