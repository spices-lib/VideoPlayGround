#include "RenderBackendInterface.h"
#include <GLFW/glfw3.h>

namespace PlayGround::GLFW {

	SP<APIInterface> CreateInterface()
	{
		 return CreateSP<VulkanInterface>();
	}

	void VulkanInterface::Hint()
	{
		// Set no OpenGL (use vulkan)
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

}