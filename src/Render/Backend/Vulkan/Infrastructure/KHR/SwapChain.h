#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Render/Backend/Vulkan/Infrastructure/Device.h"
#include <GLFW/glfw3.h>

namespace PlayGround::Vulkan {

	class SwapChain : public Infrastructure
	{
	public:

		static constexpr EInfrastructure Type = EInfrastructure::SwapChain;

	public:

		SwapChain(Context& context, GLFWwindow* window);

		~SwapChain() override = default;

		VkSwapchainKHR& Handle() { return m_Handle; }

	private:

		void Create(GLFWwindow* window);

	private:

		VkSwapchainKHR m_Handle = nullptr;

	};

	template<>
	inline void Infrastructure::Destroy(SwapChain* infrastructure)
	{
		const auto device = infrastructure->m_Context.Get<Device>()->Handle();

		vkDestroySwapchainKHR(device, infrastructure->Handle(), nullptr);
		infrastructure->Handle() = nullptr;
	}

}