#include "VideoSession.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Render/Backend/Vulkan/Infrastructure/PhysicalDevice.h"

namespace PlayGround::Vulkan {

	VideoSession::VideoSession(Context& context)
		 : ContextAccessor(context) 
	{
		m_VideoSession.SetFunctor(
			GetContext().Get<IFunctions>()->vkCreateVideoSessionKHR, 
			GetContext().Get<IFunctions>()->vkDestroyVideoSessionKHR
		);

		m_VideoSessionParameters.SetFunctor(
			GetContext().Get<IFunctions>()->vkCreateVideoSessionParametersKHR, 
			GetContext().Get<IFunctions>()->vkDestroyVideoSessionParametersKHR, 
			GetContext().Get<IFunctions>()->vkUpdateVideoSessionParametersKHR
		);
	}

	void VideoSession::CreateVideoSession()
	{
        VkVideoDecodeH265ProfileInfoKHR             decodeH265Profile{};
		decodeH265Profile.sType                   = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_PROFILE_INFO_KHR;
		decodeH265Profile.stdProfileIdc           = STD_VIDEO_H265_PROFILE_IDC_MAIN;
		decodeH265Profile.pNext                   = nullptr;
										         
		VkVideoProfileInfoKHR                       profile{};
		profile.sType                             = VK_STRUCTURE_TYPE_VIDEO_PROFILE_INFO_KHR;
		profile.videoCodecOperation               = VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR;
		profile.chromaSubsampling                 = VK_VIDEO_CHROMA_SUBSAMPLING_420_BIT_KHR;
		profile.lumaBitDepth                      = VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR;
		profile.chromaBitDepth                    = VK_VIDEO_COMPONENT_BIT_DEPTH_8_BIT_KHR;
		profile.pNext                             = &decodeH265Profile;

		auto property = GetContext().Get<IPhysicalDevice>()->QueryVideoSessionProperty({ profile });

		VkVideoSessionCreateFlagsKHR                sessionFlags{};
											      
		VkExtensionProperties                       h265Version{ VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_EXTENSION_NAME };
		h265Version.specVersion                   = VK_STD_VULKAN_VIDEO_CODEC_H265_DECODE_SPEC_VERSION;
											      
		VkVideoSessionCreateInfoKHR                 info{};
		info.sType                                = VK_STRUCTURE_TYPE_VIDEO_SESSION_CREATE_INFO_KHR;
		info.flags                                = sessionFlags;
		info.pVideoProfile                        = &profile;
		info.queueFamilyIndex                     = GetContext().Get<IPhysicalDevice>()->GetQueueFamilies().videoEncode.value();
		info.pictureFormat                        = property.dstFormat;
		info.maxCodedExtent                       = property.capabilities.maxCodedExtent;
		info.maxDpbSlots                          = property.capabilities.maxDpbSlots;
		info.maxActiveReferencePictures           = property.capabilities.maxDpbSlots;
		info.referencePictureFormat               = property.dpbFormat;
		info.pStdHeaderVersion                    = &h265Version;
		info.pNext                                = nullptr;

		m_VideoSession.CreateVideoSession(GetContext().Get<IDevice>()->Handle(), info);

		DEBUGUTILS_SETOBJECTNAME(m_VideoSession, "VideoSession")

		uint32_t memoryRequirementsCount = 0;
		VK_CHECK(GetContext().Get<IFunctions>()->vkGetVideoSessionMemoryRequirementsKHR(GetContext().Get<IDevice>()->Handle(), Handle(), &memoryRequirementsCount, NULL))

		std::vector<VkVideoSessionMemoryRequirementsKHR> memoryRequirements(memoryRequirementsCount, { VK_STRUCTURE_TYPE_VIDEO_SESSION_MEMORY_REQUIREMENTS_KHR });
		VK_CHECK(GetContext().Get<IFunctions>()->vkGetVideoSessionMemoryRequirementsKHR(GetContext().Get<IDevice>()->Handle(), Handle(), &memoryRequirementsCount, memoryRequirements.data()))

        std::vector<VkBindVideoSessionMemoryInfoKHR> sessionBindMemorys(memoryRequirementsCount, { VK_STRUCTURE_TYPE_BIND_VIDEO_SESSION_MEMORY_INFO_KHR });

        for (uint32_t i = 0; i < memoryRequirementsCount; i++) 
        {
            uint32_t memoryTypeIndex = 0;
            uint32_t memoryTypeBits = memoryRequirements[i].memoryRequirements.memoryTypeBits;

            while(!(memoryTypeBits & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT))
            {
                memoryTypeIndex++;
                memoryTypeBits >>= 1;
            }

            VkMemoryAllocateInfo                           memInfo{};
            memInfo.sType                                = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            memInfo.allocationSize                       = memoryRequirements[i].memoryRequirements.size;
            memInfo.memoryTypeIndex                      = memoryTypeIndex;
            memInfo.pNext                                = nullptr;

            VK_CHECK(vkAllocateMemory(GetContext().Get<IDevice>()->Handle(), &memInfo, nullptr, &m_Memorys[i]))

            VkBindVideoSessionMemoryInfoKHR&               sessionBindMemory = sessionBindMemorys[i];
            sessionBindMemory.sType                      = VK_STRUCTURE_TYPE_BIND_VIDEO_SESSION_MEMORY_INFO_KHR;
            sessionBindMemory.memory                     = m_Memorys[i];
            sessionBindMemory.memoryBindIndex            = memoryRequirements[i].memoryBindIndex;
            sessionBindMemory.memoryOffset               = 0;
            sessionBindMemory.memorySize                 = memoryRequirements[i].memoryRequirements.size;
            sessionBindMemory.pNext                      = nullptr;
        }

        VK_CHECK(GetContext().Get<IFunctions>()->vkBindVideoSessionMemoryKHR(GetContext().Get<IDevice>()->Handle(), Handle(), memoryRequirementsCount, sessionBindMemorys.data()))
	}

	void VideoSession::CreateVideoSessionParameters()
	{
		VkVideoDecodeH265SessionParametersAddInfoKHR       decodeH265AddInfo{};
		decodeH265AddInfo.sType                          = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_ADD_INFO_KHR;

		VkVideoDecodeH265SessionParametersCreateInfoKHR    decodeH265CreateInfo {};
		decodeH265CreateInfo.sType                       = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_CREATE_INFO_KHR;
		decodeH265CreateInfo.maxStdVPSCount              = 16;
		decodeH265CreateInfo.maxStdSPSCount              = 32;
		decodeH265CreateInfo.maxStdPPSCount              = 256;
		decodeH265CreateInfo.pParametersAddInfo          = &decodeH265AddInfo;
		decodeH265CreateInfo.pNext                       = nullptr;

		VkVideoSessionParametersCreateInfoKHR              createInfo{};
		createInfo.sType                                 = VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_CREATE_INFO_KHR;
		createInfo.flags                                 = 0;
		createInfo.videoSessionParametersTemplate        = nullptr;
		createInfo.videoSession                          = Handle();
		createInfo.pNext                                 = &decodeH265CreateInfo;

		m_VideoSessionParameters.CreateVideoSessionParameters(GetContext().Get<IDevice>()->Handle(), createInfo);
	}

	void VideoSession::UpdateVideoSessionParameters()
	{
		VkVideoDecodeH265SessionParametersAddInfoKHR       decodeH265AddInfo{};
		decodeH265AddInfo.sType                          = VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_SESSION_PARAMETERS_ADD_INFO_KHR;

		StdVideoH265VideoParameterSet vps{};
		// parse and populate VPS parameters

		StdVideoH265SequenceParameterSet sps{};
		// parse and populate SPS parameters

		StdVideoH265PictureParameterSet pps{};
		// parse and populate PPS parameters

		VkVideoSessionParametersUpdateInfoKHR              updateInfo {};
		updateInfo.sType                                 = VK_STRUCTURE_TYPE_VIDEO_SESSION_PARAMETERS_UPDATE_INFO_KHR;
		updateInfo.updateSequenceCount                   = 1;
		updateInfo.pNext                                 = &decodeH265AddInfo;

		m_VideoSessionParameters.UpdateVideoSessionParameters(GetContext().Get<IDevice>()->Handle(), updateInfo);
	}
}