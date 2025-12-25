#pragma once
#include "Core/Core.h"
#include "Unit.h"
#include <vector>

namespace PlayGround::Vulkan::Unit {

	class VideoSessionParameters : public Unit<VkVideoSessionParametersKHR, VkObjectType::VK_OBJECT_TYPE_VIDEO_SESSION_PARAMETERS_KHR>
	{
	public:

		using Handle = Unit::Handle;

	public:

		VideoSessionParameters() : Unit() {}

		~VideoSessionParameters() override;

		void SetFunctor(PFN_vkCreateVideoSessionParametersKHR create, PFN_vkDestroyVideoSessionParametersKHR destroy, PFN_vkUpdateVideoSessionParametersKHR update);

		void CreateVideoSessionParameters(VkDevice device, const VkVideoSessionParametersCreateInfoKHR& createInfo);

		void UpdateVideoSessionParameters(VkDevice device, const VkVideoSessionParametersUpdateInfoKHR& updateInfo);

	private:

		VkDevice                               m_Device = nullptr;
		PFN_vkCreateVideoSessionParametersKHR  vkCreateVideoSessionParametersKHR = nullptr;
		PFN_vkDestroyVideoSessionParametersKHR vkDestroyVideoSessionParametersKHR = nullptr;
		PFN_vkUpdateVideoSessionParametersKHR  vkUpdateVideoSessionParametersKHR = nullptr;
	};
}