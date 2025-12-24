#include "Surface.h"
#include <GLFW/glfw3.h>

namespace PlayGround::Vulkan::Unit {

	Surface::~Surface()
	{
		if (!m_Handle || !m_Instance) return;

		vkDestroySurfaceKHR(m_Instance, m_Handle, nullptr);
		ResetHandle();
	}

	void Surface::CreateSurface(VkInstance instance, GLFWwindow* window)
	{
		assert(instance && window && !m_Handle);

		m_Instance = instance;

		VK_CHECK(glfwCreateWindowSurface(instance, window, nullptr, &m_Handle))
	}
}