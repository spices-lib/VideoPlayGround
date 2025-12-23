#pragma once

#include "Core/Core.h"
#include "Infrastructure.h"

namespace PlayGround::Vulkan {

	class Device : public Infrastructure
	{
	public:

		static constexpr EInfrastructure Type = EInfrastructure::Device;

	public:

		Device(Context& context);

		~Device() override = default;

		VkDevice& Handle() { return m_Handle; }

	private:

		void Create();

	private:

		VkDevice m_Handle = nullptr;

	};

	template<>
	inline void Infrastructure::Destroy(Device* infrastructure)
	{
		vkDestroyDevice(infrastructure->Handle(), nullptr);
		infrastructure->Handle() = nullptr;
	}

}