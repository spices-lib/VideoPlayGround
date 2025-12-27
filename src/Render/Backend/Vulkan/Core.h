#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/ContextAccessor.h"
#include "Render/Frontend/Utils.h"
#include <vulkan/vulkan.h>
#include <sstream>

namespace PlayGround::Vulkan {

	constexpr uint32_t MaxFrameInFlight = PlayGround::MaxFrameInFlight;

	constexpr uint32_t NThreadQueue = 4;

	#define VMA_ALLOCATOR 0

	#define VKImageHostOperation 0

	static void HandleVulkanResult(VkResult result)
	{
		if (result == VK_SUCCESS) return;

		const char* label = "";
		switch (result)
		{
			case VK_NOT_READY:                                           label = "Not Ready"; break;
			case VK_TIMEOUT:                                             label = "Time out"; break;
			case VK_EVENT_SET:                                           label = "Event Set"; break;
			case VK_EVENT_RESET:                                         label = "Event Reset"; break;
			case VK_INCOMPLETE:                                          label = "Incomplete"; break;
			case VK_ERROR_OUT_OF_HOST_MEMORY:                            label = "Out of Host Memory"; break;
			case VK_ERROR_OUT_OF_DEVICE_MEMORY:                          label = "Out of Device Memory"; break;
			case VK_ERROR_INITIALIZATION_FAILED:                         label = "Initializtion Failed"; break;
			case VK_ERROR_DEVICE_LOST:                                   label = "Device Lost"; break;
			case VK_ERROR_MEMORY_MAP_FAILED:                             label = "Memory Map Failed"; break;
			case VK_ERROR_LAYER_NOT_PRESENT:                             label = "Layer not Present"; break;
			case VK_ERROR_EXTENSION_NOT_PRESENT:                         label = "Extension not Present"; break;
			case VK_ERROR_FEATURE_NOT_PRESENT:                           label = "Feature not Present"; break;
			case VK_ERROR_INCOMPATIBLE_DRIVER:                           label = "Incompatible Driver"; break;
			case VK_ERROR_TOO_MANY_OBJECTS:                              label = "Too Many Objects"; break;
			case VK_ERROR_FORMAT_NOT_SUPPORTED:                          label = "Format not supported"; break;
			case VK_ERROR_SURFACE_LOST_KHR:                              label = "Surface Lost"; break;
			case VK_SUBOPTIMAL_KHR:                                      label = "Suboptimal"; break;
			case VK_ERROR_OUT_OF_DATE_KHR:                               label = "Out of Data"; break;
			case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:                      label = "Incompatible Display"; break;
			case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:                      label = "Native Window In Use"; break;
			case VK_ERROR_VALIDATION_FAILED_EXT:                         label = "Validation Failed"; break;
			case VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR:        label = "Video Profile Format Not Supported"; break;
			default:                                                     label = "Unkonwn Error"; break;
		}

		std::stringstream ss;
		ss << "Vulkan Error: [ " << label << " ]: ";

		CORE_ERROR(ss.str())
	}

	#define VK_CHECK(expr)  { auto expr_value = expr; HandleVulkanResult(expr_value); }

	/**
	* @brief This struct contains all Vulkan object in used global.
	*/
	//struct VulkanState : NonCopyable
	//{
	//	/**
	//	* @brief Constructor Function.
	//	*/
	//	VulkanState() = default;
	//	
	//	VkInstance                                       m_Instance;                   /* @brief From VulkanInstance.                                            */
	//	VkSurfaceKHR                                     m_Surface;                    /* @brief From VulkanInstance.                                            */
	//	VkPhysicalDevice                                 m_PhysicalDevice;             /* @brief From VulkanDevice.                                              */
	//	VkDevice                                         m_Device;                     /* @brief From VulkanDevice.                                              */
	//	`VmaAllocator                                     m_VmaAllocator;               /* @brief From VulkanMemoryAllocator.                                     */
	//	VulkanFunctions                                  m_VkFunc;                     /* @brief From VulkanFunctions.                                           */
	//	VkQueue											 m_GraphicQueue;               /* @brief From VulkanDevice, Queue for graphic compute.                   */
	//	uint32_t                                         m_GraphicQueueFamily;         /* @brief From VulkanDevice, ID for graphic queue.                        */
	//	VkQueue											 m_PresentQueue;               /* @brief From VulkanDevice, Queue for present windows.                   */
	//	VkQueue											 m_TransferQueue;              /* @brief From VulkanDevice, Queue for transfer buffer.                   */
	//	VkQueue											 m_ComputeQueue;               /* @brief From VulkanDevice, Queue for compute shader.                    */
	//	uint32_t                                         m_ComputeQueueFamily;         /* @brief From VulkanDevice, ID for compute queue.                        */
	//	VkSwapchainKHR                                   m_SwapChain;                  /* @brief From VulkanSwapChain.                                           */
	//	std::array<VkImage,           MaxFrameInFlight>  m_SwapChainImages;            /* @brief The SwapChain's image, used for present.                        */
	//	std::array<VkImageView,       MaxFrameInFlight>  m_SwapChainImageViews;        /* @brief The SwapChain's imageView.                                      */
	//	std::array<VkSampler,         MaxFrameInFlight>  m_SwapChainImageSamplers;     /* @brief The SwapChain's imageSampler.                                   */
	//  													 
	//	// Used for Graphic Queue	  					 
	//	VkCommandPool                                    m_GraphicCommandPool;         /* @brief From VulkanCommandBuffer                                        */
	//	std::array<VkCommandBuffer,   MaxFrameInFlight>  m_GraphicCommandBuffer;       /* @brief From VulkanCommandBuffer, Array num equals to MaxFrameInFlight. */
	//	std::array<VkSemaphore,       MaxFrameInFlight>  m_GraphicImageSemaphore;      /* @brief From VulkanSwapChain, Array num equals to MaxFrameInFlight.     */
	//	std::array<VkSemaphore,       MaxFrameInFlight>  m_GraphicQueueSemaphore;      /* @brief From VulkanSwapChain, Array num equals to MaxFrameInFlight.     */
	//	std::array<VkFence,           MaxFrameInFlight>  m_GraphicFence;               /* @brief From VulkanSwapChain, Array num equals to MaxFrameInFlight.     */
	//								  					 
	//	// Use for Compute Queue.	  					 
	//	VkCommandPool                                    m_ComputeCommandPool;         /* @brief From VulkanCommandBuffer                                        */
	//	std::array<VkCommandBuffer,   MaxFrameInFlight>  m_ComputeCommandBuffer;       /* @brief From VulkanCommandBuffer, Array num equals to MaxFrameInFlight. */
	//	std::array<VkSemaphore,       MaxFrameInFlight>  m_ComputeQueueSemaphore;      /* @brief From VulkanSwapChain, Array num equals to MaxFrameInFlight.     */
	//	std::array<VkFence,           MaxFrameInFlight>  m_ComputeFence;               /* @brief From VulkanSwapChain, Array num equals to MaxFrameInFlight.     */
	//};


}