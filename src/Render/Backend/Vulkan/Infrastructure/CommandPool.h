#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"

namespace PlayGround::Vulkan {

	class CommandPool : public Infrastructure
	{
	public:

		static constexpr EInfrastructure Type = EInfrastructure::CommandPool;

	public:

		CommandPool(Context& context);

		~CommandPool() override = default;

		VkCommandPool& Handle() { return m_Handle; }

	private:

		void Create();

	private:

		VkCommandPool m_Handle = nullptr;

	};

	template<>
	inline void Infrastructure::Destroy(CommandPool* infrastructure)
	{

	}

}