#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/Instance.h"
#include "Functions.h"
#include <vector>

namespace PlayGround::Vulkan {

	using IInstance = InfrastructureClass<class Instance, EInfrastructure::Instance>;

	class Instance : public Infrastructure
	{
	public:

		Instance(Context& context, EInfrastructure e);

		~Instance() override;

		const VkInstance& Handle() { return m_Instance.GetHandle(); }
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

		Unit::Instance m_Instance;
		std::vector<const char*> m_ExtensionProperties;
		std::vector<const char*> m_LayerProperties;
		VkDebugUtilsMessengerEXT m_DebugMessenger{};
		VkDebugUtilsMessengerCreateInfoEXT m_DebugMessengerCreateInfo{};
	};

}