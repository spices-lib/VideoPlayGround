#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/Instance.h"
#include "Functions.h"
#include <vector>

namespace PlayGround::Vulkan {

	class Instance : public Infrastructure
	{
	public:

		static constexpr EInfrastructure Type = EInfrastructure::Instance;

	public:

		Instance(Context& context);

		~Instance() override = default;

		VkInstance& Handle() { return m_Handle; }
		VkDebugUtilsMessengerEXT& DebugMessenger() { return m_DebugMessenger; }

	private:

		void Create();

		void GetExtensionRequirements();

		bool CheckExtensionRequirementsSatisfied();

		void GetLayerRequirements();

		bool ChecklayerRequirementsSatisfied();

		void SetVulkanDebugCallbackFuncPointer();

		void FillDebugMessengerCreateInfo();

	private:

		Unit::Instance instance;
		std::vector<const char*> m_ExtensionProperties;
		std::vector<const char*> m_LayerProperties;
		VkDebugUtilsMessengerEXT m_DebugMessenger{};
		VkDebugUtilsMessengerCreateInfoEXT m_DebugMessengerCreateInfo{};
	};

	template<>
	inline void Infrastructure::Destroy(Instance* infrastructure)
	{
#ifdef PG_DEBUG

		infrastructure->m_Context.Get<Functions>()->vkDestroyDebugUtilsMessengerEXT(infrastructure->Handle(), infrastructure->DebugMessenger(), nullptr);

#endif

		vkDestroyInstance(infrastructure->Handle(), nullptr);
		infrastructure->Handle() = nullptr;
	}

}