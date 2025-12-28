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
		std::optional<uint32_t> videoEncode;

		bool isComplete() const
		{
			return graphic.has_value() && present.has_value() && transfer.has_value() && compute.has_value() && videoEncode.has_value();
		}
	};

	struct SwapChainProperty
	{
		VkSurfaceCapabilitiesKHR        capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR>   presentModes;
		VkSurfaceFormatKHR              format;
		VkPresentModeKHR                presentMode;
		VkExtent2D                      surfaceSize;
		VkExtent2D                      viewPortSize = { 1280, 960 };
	};

	struct VideoSessionProperty
	{
		VkVideoCapabilitiesKHR          capabilities;
		VkFormat                        dpbFormat;
		VkFormat                        dstFormat;
	};

	using IPhysicalDevice = InfrastructureClass<class PhysicalDevice, EInfrastructure::PhysicalDevice>;

	class PhysicalDevice : public Infrastructure
	{
	public:

		PhysicalDevice(Context& context, EInfrastructure e);

		~PhysicalDevice() override = default;

		const VkPhysicalDevice& Handle() const { return m_PhysicalDevice.GetHandle(); }

		const std::vector<const char*>& GetExtensionRequirements();

		const QueueFamilies& GetQueueFamilies() const { return m_QueueFamilies; }

		const VkPhysicalDeviceProperties& GetProperties() const { return m_Properties; };

		const SwapChainProperty& GetSwapChainProperty() { return m_SwapChainProperty; }

		VideoSessionProperty QueryVideoSessionProperty(const std::vector<VkVideoProfileInfoKHR>& videoProfiles);

		const SwapChainProperty& QuerySwapChainProperty(GLFWwindow* window);

	private:

		void Create();

		bool IsExtensionMeetDemand(const VkPhysicalDevice& device);

		bool IsPropertyMeetDemand(const VkPhysicalDevice& device);

		bool IsFeatureMeetDemand(const VkPhysicalDevice& device);

		bool IsQueueMeetDemand(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);

		std::vector<VkFormat> GetVideoFormats(VkImageUsageFlags imageUsage, const std::vector<VkVideoProfileInfoKHR>& videoProfile);

	private:

		Unit::PhysicalDevice m_PhysicalDevice;
		std::vector<const char*> m_ExtensionProperties;
		QueueFamilies m_QueueFamilies;
		VkPhysicalDeviceProperties m_Properties;
		SwapChainProperty m_SwapChainProperty;
	};

}