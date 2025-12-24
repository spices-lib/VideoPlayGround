#pragma once
#include "Core/Core.h"
#include "Unit.h"

struct GLFWwindow;

namespace PlayGround::Vulkan::Unit {

	class Surface : public Unit<VkSurfaceKHR, VkObjectType::VK_OBJECT_TYPE_SURFACE_KHR>
	{
	public:

		using Handle = Unit::Handle;

	public:

		Surface() : Unit() {}

		~Surface() override;

		void CreateSurface(VkInstance instance, GLFWwindow* window);

	private:

		VkInstance m_Instance;
	};
}