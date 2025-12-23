#include "Instance.h"
#include <set>
#include <GLFW/glfw3.h>

namespace PlayGround::Vulkan {

	namespace {

		VKAPI_ATTR VkBool32 VKAPI_CALL InstanceDebugCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT         messageSeverity, 
			VkDebugUtilsMessageTypeFlagsEXT                messageType, 
			const VkDebugUtilsMessengerCallbackDataEXT*    pCallbackData, 
			void*                                          pUserData
		)
		{
			std::stringstream ss;

			ss <<
			"validation layer:\n			" <<
			"MessageIdNumber: " <<
			pCallbackData->messageIdNumber <<
			"\n			MessageIdName: " <<
			pCallbackData->pMessageIdName;

			if (pCallbackData->cmdBufLabelCount != 0)
			{
				ss << "\n		CmdLabelName: " <<
				pCallbackData->pCmdBufLabels->pLabelName;
			}

			ss <<
			"\n			Message: " <<
			pCallbackData->pMessage;

			switch (messageSeverity)
			{
				case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
					CORE_TRACE(ss.str())
					break;

				case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
					CORE_INFO(ss.str())
					break;

				case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
					CORE_WARN(ss.str())
					break;

				case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
					CORE_ERROR(ss.str())
					break;
			
				case VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT:
					break;
			
				default:
					break;
			}
	
			return VK_FALSE;
		}

	}

    Instance::Instance(Context& context)
        : Infrastructure(context)
    {
        Create();
    }

    void Instance::Create()
    {
        VkApplicationInfo                          appInfo {};
		appInfo.sType                            = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName                 = "playground";
		appInfo.applicationVersion               = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName                      = "playground";
		appInfo.engineVersion                    = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion                       = VK_API_VERSION_1_4;

        VkInstanceCreateInfo                       createInfo {};
		createInfo.sType                         = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo              = &appInfo;

		GetExtensionRequirements();
		if (!CheckExtensionRequirementsSatisfied())
		{
			std::stringstream ss;
			ss << "Instance Extension not Satisfied";

			CORE_ERROR(ss.str());
			return;
		}

		createInfo.enabledExtensionCount         = static_cast<uint32_t>(m_ExtensionProperties.size());
		createInfo.ppEnabledExtensionNames       = m_ExtensionProperties.data();

		GetLayerRequirements();
		if (!ChecklayerRequirementsSatisfied())
		{
			std::stringstream ss;
			ss << "Instance Layer not Satisfied";

			CORE_ERROR(ss.str());
			return;
		}

		createInfo.enabledLayerCount             = static_cast<uint32_t>(m_LayerProperties.size());
		createInfo.ppEnabledLayerNames           = m_LayerProperties.data();

		FillDebugMessengerCreateInfo();

		createInfo.pNext = &m_DebugMessengerCreateInfo;

		std::vector<VkValidationFeatureEnableEXT> validationFeatureEnable;

#if 0

		validationFeatureEnable.push_back(VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT);
	
#endif

#ifdef PG_DEBUG

		VkValidationFeaturesEXT								  validationFeatures{};
		validationFeatures.sType						    = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
		validationFeatures.enabledValidationFeatureCount    = static_cast<uint32_t>(validationFeatureEnable.size());
		validationFeatures.pEnabledValidationFeatures       = validationFeatureEnable.data();

		m_DebugMessengerCreateInfo.pNext                    = &validationFeatures;

#endif

        VK_CHECK(vkCreateInstance(&createInfo, nullptr, &m_Handle))

		m_Context.Registry<Functions>();
		m_Context.Get<Functions>()->Init(m_Handle);

		SetVulkanDebugCallbackFuncPointer();
    }

    void Instance::GetExtensionRequirements()
	{
		m_ExtensionProperties.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
		m_ExtensionProperties.push_back(VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME);

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		for (uint32_t i = 0; i < glfwExtensionCount; i++) 
		{
			m_ExtensionProperties.push_back(*glfwExtensions);
			glfwExtensions++;
		}

#ifdef PG_DEBUG

		m_ExtensionProperties.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

#endif
	}

	bool Instance::CheckExtensionRequirementsSatisfied()
	{
		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());
		
		std::set<std::string> requiredExtensions(m_ExtensionProperties.begin(), m_ExtensionProperties.end());

		for (const auto& extension : availableExtensions) 
		{
			requiredExtensions.erase(extension.extensionName);
		}

		if (!requiredExtensions.empty())
		{
			for (auto& set : requiredExtensions)
			{
				std::stringstream ss;
				ss << "Instance Extension Required: " << set << ", Which is not satisfied";
				
				CORE_WARN(ss.str())
			}
		}

		return requiredExtensions.empty();
	}

	void Instance::GetLayerRequirements()
	{
		
#ifdef PG_DEBUG

		m_LayerProperties.push_back("VK_LAYER_KHRONOS_validation");

#endif

	}

	bool Instance::ChecklayerRequirementsSatisfied()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		std::set<std::string> requiredLayers(m_LayerProperties.begin(), m_LayerProperties.end());

		for (const auto& layer : availableLayers) 
		{
			requiredLayers.erase(layer.layerName);
		}

		if (!requiredLayers.empty())
		{
			for (auto& set : requiredLayers)
			{
				std::stringstream ss;
				ss << "Instance Layer Required: " << set << ", Which is not satisfied";
				
				CORE_WARN(ss.str())
			}
		}

		return requiredLayers.empty();
	}

	void Instance::SetVulkanDebugCallbackFuncPointer()
	{

#ifdef PG_DEBUG

		m_Context.Get<Functions>()->vkCreateDebugUtilsMessengerEXT(m_Handle, &m_DebugMessengerCreateInfo, nullptr, &m_DebugMessenger);

#endif

	}

	void Instance::FillDebugMessengerCreateInfo()
	{
		m_DebugMessengerCreateInfo                     = VkDebugUtilsMessengerCreateInfoEXT {};
		m_DebugMessengerCreateInfo.sType               = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		
		m_DebugMessengerCreateInfo.messageSeverity     = 
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT   |
			VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT    ;
		
		m_DebugMessengerCreateInfo.messageType         = 
			VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT      |
			VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT   | 
			VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT  ;
		
		m_DebugMessengerCreateInfo.pfnUserCallback     = InstanceDebugCallback;
		m_DebugMessengerCreateInfo.pUserData           = nullptr;
		m_DebugMessengerCreateInfo.pNext               = nullptr;
	}
}