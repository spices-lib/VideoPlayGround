#include "PhysicalDevice.h"
#include "Instance.h"
#include "Surface.h"
#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <algorithm>

namespace PlayGround::Vulkan {

	PhysicalDevice::PhysicalDevice(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        Create();
    }

	void PhysicalDevice::Create()
    {
        const auto instance = GetContext().Get<IInstance>()->Handle();

        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

        if (deviceCount == 0) 
		{
			CORE_ERROR("Failed to find GPUs with Vulkan support.")
			return;
		}

        std::vector<VkPhysicalDevice> PhysicalDevices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, PhysicalDevices.data());

		// Iter all physical and select one suitable.
		for (const auto& physicalDevice : PhysicalDevices)
		{
			// All this condition need satisfied.
			if (IsExtensionMeetDemand(physicalDevice) && IsPropertyMeetDemand(physicalDevice) && IsFeatureMeetDemand(physicalDevice) &&
				IsQueueMeetDemand(physicalDevice, GetContext().Get<ISurface>()->Handle()))
			{
				m_PhysicalDevice.SetHandle(physicalDevice);

				CORE_INFO("Vulkan PhysicalDevice Selected.")
				return;
			}
		}

		CORE_ERROR("Failed to find GPU Physical Device that satisfied our needs.")
    }

	bool PhysicalDevice::IsExtensionMeetDemand(const VkPhysicalDevice& device)
	{
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		auto requiredList = GetExtensionRequirements();
		std::set<std::string> requiredExtensions(requiredList.begin(), requiredList.end());

		for (const auto& extension : availableExtensions)
		{
			requiredExtensions.erase(extension.extensionName);
		}

		if (requiredExtensions.empty())
		{
			return true;
		}
		else
		{
			// Get Physical Device name.
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(device, &deviceProperties);

			for (auto& set : requiredExtensions)
			{
				std::stringstream ss;
				ss << "Device Extension Required: [ " << set << " ], Which is not satisfied with device: " << deviceProperties.deviceName;

				CORE_ERROR(ss.str())
			}

			return false;
		}
	}

	bool PhysicalDevice::IsPropertyMeetDemand(const VkPhysicalDevice& device)
	{
		VkPhysicalDeviceProperties2                   prop2 {};
		prop2.sType                                 = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
		prop2.pNext                                 = nullptr;

		vkGetPhysicalDeviceProperties2(device, &prop2);

		m_Properties = prop2.properties;

		return true;
	}

	bool PhysicalDevice::IsFeatureMeetDemand(const VkPhysicalDevice& device)
	{
		VkPhysicalDeviceFeatures2                             deviceFeatures {};
		deviceFeatures.sType                                = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
		deviceFeatures.pNext                                = nullptr;

		vkGetPhysicalDeviceFeatures2(device, &deviceFeatures);

		return true;
	}

	bool PhysicalDevice::IsQueueMeetDemand(const VkPhysicalDevice& device, const VkSurfaceKHR& surface)
	{
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties2(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties2> queueFamilies(queueFamilyCount,{ VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2 });
		vkGetPhysicalDeviceQueueFamilyProperties2(device, &queueFamilyCount, queueFamilies.data());

		for (uint32_t i = 0; i < queueFamilyCount; i++) 
		{
			const auto& queueFamily = queueFamilies[i];

			if (queueFamily.queueFamilyProperties.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				m_QueueFamilies.graphic = i;

				VkBool32 presentSupport = false;
				vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

				if (presentSupport) 
				{
					m_QueueFamilies.present = i;
				}
			}
			else
			{
				// Get compute queue identify.
				if (queueFamily.queueFamilyProperties.queueFlags & VK_QUEUE_COMPUTE_BIT && !m_QueueFamilies.compute.has_value()) 
				{
					m_QueueFamilies.compute = i;
				}

				// Get transfer queue identify.
				if (queueFamily.queueFamilyProperties.queueFlags & VK_QUEUE_TRANSFER_BIT && !m_QueueFamilies.transfer.has_value()) 
				{
					m_QueueFamilies.transfer = i;
				}

				// Get video encode queue identify.
				if (queueFamily.queueFamilyProperties.queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR && !m_QueueFamilies.videoEncode.has_value()) 
				{
					m_QueueFamilies.videoEncode = i;
				}
			}

			if (m_QueueFamilies.isComplete()) return true;
		}

		return false;
	}

	VideoSessionProperty PhysicalDevice::QueryVideoSessionProperty(const std::vector<VkVideoProfileInfoKHR>& videoProfiles)
	{
		VideoSessionProperty property{};

		VkVideoDecodeH265ProfileInfoKHR       decodeH265ProfileInfo{};
		decodeH265ProfileInfo.sType         = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PROFILE_INFO_KHR;
		decodeH265ProfileInfo.stdProfileIdc = STD_VIDEO_H265_PROFILE_IDC_MAIN;
		decodeH265ProfileInfo.pNext         = nullptr;

		VkVideoProfileInfoKHR                 profileInfo {};
		profileInfo.sType                   = VK_STRUCTURE_TYPE_VIDEO_PROFILE_INFO_KHR;
		profileInfo.videoCodecOperation     = VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR;
		profileInfo.chromaSubsampling       = VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR;
		profileInfo.lumaBitDepth            = VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR;
		profileInfo.chromaBitDepth          = VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR;
		profileInfo.pNext                   = &decodeH265ProfileInfo;

		VkVideoDecodeH265CapabilitiesKHR      decodeH265Capabilities{};
		decodeH265Capabilities.sType        = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_CAPABILITIES_KHR;
		decodeH265Capabilities.pNext        = nullptr;

		VkVideoDecodeCapabilitiesKHR          decodeCapabilities{};
		decodeCapabilities.sType            = VK_STRUCTURE_TYPE_VIDEO_DECODE_CAPABILITIES_KHR;
		decodeCapabilities.pNext            = &decodeH265Capabilities;

		VkVideoCapabilitiesKHR&                capabilities = property.capabilities;
		capabilities.sType                  = VK_STRUCTURE_TYPE_VIDEO_CAPABILITIES_KHR;
		capabilities.pNext                  = &decodeCapabilities;

		VK_CHECK(GetContext().Get<IFunctions>()->vkGetPhysicalDeviceVideoCapabilitiesKHR(Handle(), &profileInfo, &capabilities));

		if (capabilities.flags & VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_COINCIDE_BIT_KHR) 
		{
			 // NV, Intel
			auto dpbFormats = GetVideoFormats(VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR | VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR, videoProfiles);

            property.dpbFormat = dpbFormats[0];
            property.dstFormat = dpbFormats[0];
		}
		else if (capabilities.flags & VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_DISTINCT_BIT_KHR) 
		{
			// AMD
			auto dpbFormats = GetVideoFormats(VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR, videoProfiles);
            auto outFormats = GetVideoFormats(VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR, videoProfiles);
           
            property.dpbFormat = dpbFormats[0];
            property.dstFormat = outFormats[0];
		}
		else
		{
            CORE_ERROR("Unsupported Decode Capability Flags.");
        }

		return property;
	}

	const SwapChainProperty& PhysicalDevice::QuerySwapChainProperty(GLFWwindow* window)
	{
		auto surface = GetContext().Get<ISurface>()->Handle();

		SwapChainProperty property{};
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(Handle(), surface, &property.capabilities);

		if (property.capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
		{
			property.surfaceSize = property.capabilities.currentExtent;
		}
		else
		{
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);

			VkExtent2D actualExtent =
			{
				static_cast<uint32_t>(width),
				static_cast<uint32_t>(height)
			};

			actualExtent.width = std::clamp(actualExtent.width, property.capabilities.minImageExtent.width, property.capabilities.maxImageExtent.width);
			actualExtent.height = std::clamp(actualExtent.height, property.capabilities.minImageExtent.height, property.capabilities.maxImageExtent.height);

			property.surfaceSize = actualExtent;
		}

		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(Handle(), surface, &formatCount, nullptr);

		if (formatCount != 0)
		{
			property.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(Handle(), surface, &formatCount, property.formats.data());

			property.format = property.formats[0];

			for (const auto& availableFormat : property.formats)
			{
				if (availableFormat.format == VK_FORMAT_A2B10G10R10_UNORM_PACK32 &&
					availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				{
					property.format = availableFormat;
					break;
				}
			}
		}

		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(Handle(), surface, &presentModeCount, nullptr);

		if (presentModeCount != 0)
		{
			property.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(Handle(), surface, &presentModeCount, property.presentModes.data());

			property.presentMode = property.presentModes[0];

			for (const auto& availablePresentMode : property.presentModes)
			{
				if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
				{
					property.presentMode = availablePresentMode;
					break;
				}
			}
		}

		m_SwapChainProperty = property;

		return m_SwapChainProperty;
	}

	const std::vector<const char*>& PhysicalDevice::GetExtensionRequirements()
	{
		static std::vector<const char*> m_ExtensionProperties;

		if (m_ExtensionProperties.empty())
		{
			m_ExtensionProperties.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_MAINTENANCE_1_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_SHADER_CLOCK_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_SHADER_NON_SEMANTIC_INFO_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_SPIRV_1_4_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_EXT_MESH_SHADER_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_SHADER_FLOAT_CONTROLS_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_FRAGMENT_SHADING_RATE_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_EXT_NESTED_COMMAND_BUFFER_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_EXT_MEMORY_BUDGET_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_VIDEO_QUEUE_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_VIDEO_ENCODE_QUEUE_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_VIDEO_DECODE_QUEUE_EXTENSION_NAME);
			m_ExtensionProperties.push_back(VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME);
		}

		return m_ExtensionProperties;
	}

	std::vector<VkFormat> PhysicalDevice::GetVideoFormats(VkImageUsageFlags imageUsage, const std::vector<VkVideoProfileInfoKHR>& videoProfile)
	{
		VkVideoProfileListInfoKHR                videoProfiles{};
		videoProfiles.sType                    = VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR;
		videoProfiles.profileCount             = videoProfile.size();
		videoProfiles.pProfiles                = videoProfile.data();
		videoProfiles.pNext                    = nullptr;
		
		VkPhysicalDeviceVideoFormatInfoKHR       videoFormatInfo {};
		videoFormatInfo.sType                  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_FORMAT_INFO_KHR;
		videoFormatInfo.imageUsage             = imageUsage;
		videoFormatInfo.pNext                  = &videoProfiles;

		uint32_t supportedFormatCount = 0;
        VK_CHECK(GetContext().Get<IFunctions>()->vkGetPhysicalDeviceVideoFormatPropertiesKHR(Handle(), &videoFormatInfo, &supportedFormatCount, nullptr))

		std::vector<VkVideoFormatPropertiesKHR> supportedFormats(supportedFormatCount, { VK_STRUCTURE_TYPE_VIDEO_FORMAT_PROPERTIES_KHR });
		VK_CHECK(GetContext().Get<IFunctions>()->vkGetPhysicalDeviceVideoFormatPropertiesKHR(Handle(), &videoFormatInfo, &supportedFormatCount, supportedFormats.data()))


		std::vector<VkFormat> formats;
		std::ranges::for_each(supportedFormats, [&](const auto& format){
			formats.emplace_back(format.format);
		});

		return formats;
	}
}