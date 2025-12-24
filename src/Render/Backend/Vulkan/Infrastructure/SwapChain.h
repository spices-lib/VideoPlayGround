#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Render/Backend/Vulkan/Infrastructure/Device.h"
#include "Render/Backend/Vulkan/Unit/SwapChain.h"
#include "Render/Backend/Vulkan/RHIResource/Image.h"
#include <GLFW/glfw3.h>

namespace PlayGround::Vulkan {

	using ISwapChain = InfrastructureClass<class SwapChain, EInfrastructure::SwapChain>;

	class SwapChain : public Infrastructure
	{
	public:

		SwapChain(Context& context, EInfrastructure e, GLFWwindow* window);

		~SwapChain() override = default;

		const VkSwapchainKHR& Handle() { return m_SwapChain.GetHandle(); }

	private:

		void Create(GLFWwindow* window);

	private:

		Unit::SwapChain m_SwapChain;
		std::array<SP<Image>, MaxFrameInFlight> m_SwapChainImage;

	};

}