#pragma once
#include "Core/Core.h"
#include "Unit.h"
#include <vector>

namespace PlayGround::Vulkan::Unit {

	class VideoSession : public Unit<VkVideoSessionKHR, VkObjectType::VK_OBJECT_TYPE_VIDEO_SESSION_KHR>
	{
	public:

		using Handle = Unit::Handle;

	public:

		VideoSession() : Unit() {}

		~VideoSession() override;

		void SetFunctor(PFN_vkCreateVideoSessionKHR create, PFN_vkDestroyVideoSessionKHR destroy);

		void CreateVideoSession(VkDevice device, const VkVideoSessionCreateInfoKHR& createInfo);

	private:

		VkDevice                     m_Device = nullptr;
		PFN_vkCreateVideoSessionKHR  vkCreateVideoSessionKHR = nullptr;
		PFN_vkDestroyVideoSessionKHR vkDestroyVideoSessionKHR = nullptr;
	};
}