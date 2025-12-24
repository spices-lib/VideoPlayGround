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

		SwapChain(Context& context, EInfrastructure e, GLFWwindow* window, uint32_t count);

		~SwapChain() override = default;

		const VkSwapchainKHR& Handle() { return m_SwapChain->GetHandle(); }

		bool GetNextImage(VkSemaphore semaphore, uint32_t& imageIndex);

		bool Present(VkPresentInfoKHR& info);

		void ReCreate(GLFWwindow* window, uint32_t count);

	private:

		void Destroy();
		void Create(GLFWwindow* window, uint32_t count);

	private:

		SP<Unit::SwapChain> m_SwapChain;
		std::vector<SP<Image>> m_SwapChainImage;

	};

}