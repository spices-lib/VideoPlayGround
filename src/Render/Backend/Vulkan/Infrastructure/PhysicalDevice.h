#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Render/Backend/Vulkan/Unit/PhysicalDevice.h"
#include <vector>
#include <optional>
#include <GLFW/glfw3.h>

namespace PlayGround::Vulkan {
	
	struct QueueFamilies
	{
		std::optional<uint32_t> graphic;
		std::optional<uint32_t> present;
		std::optional<uint32_t> transfer;
		std::optional<uint32_t> compute;

		bool isComplete() const
		{
			return graphic.has_value() && present.has_value() && transfer.has_value() && compute.has_value();
		}
	};

	struct SwapChainpProperty
	{
		VkSurfaceCapabilitiesKHR        capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR>   presentModes;
		VkSurfaceFormatKHR              format;
		VkPresentModeKHR                presentMode;
		VkExtent2D                      surfaceSize;
		VkExtent2D                      viewPortSize = { 1280, 960 };
	};

	using IPhysicalDevice = InfrastructureClass<class PhysicalDevice, EInfrastructure::PhysicalDevice>;

	class PhysicalDevice : public Infrastructure
	{
	public:

		PhysicalDevice(Context& context, EInfrastructure e);

		~PhysicalDevice() override = default;

		const VkPhysicalDevice& Handle() { return m_PhysicalDevice.GetHandle(); }

		const std::vector<const char*>& GetExtensionRequirements();

		const QueueFamilies& GetQueueFamilies() { return m_QueueFamilies; }

		const VkPhysicalDeviceProperties& GetProperties() { return m_Properties; };

		SwapChainpProperty QuerySwapChainSupport(GLFWwindow* window);

	private:

		void Create();

	private:

		bool IsExtensionMeetDemand(const VkPhysicalDevice& device);

		bool IsPropertyMeetDemand(const VkPhysicalDevice& device);

		bool IsFeatureMeetDemand(const VkPhysicalDevice& device);

		bool IsQueueMeetDemand(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);

	private:

		Unit::PhysicalDevice m_PhysicalDevice;
		std::vector<const char*> m_ExtensionProperties;
		QueueFamilies m_QueueFamilies;
		VkPhysicalDeviceProperties m_Properties;
	};

}