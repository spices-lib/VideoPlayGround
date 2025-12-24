#include "Image.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"

namespace PlayGround::Vulkan {

	void Image::SetImage(VkImage image)
	{
		m_Image.SetHandle(image);
	}

	void Image::CreateImageView(VkDevice device, VkImageViewCreateInfo& info)
	{
		assert(m_Image.GetHandle());

		info.image = m_Image.GetHandle();

		m_ImageView.CreateImageView(device, info);
	}

	void Image::CreateSampler(VkDevice device, VkSamplerCreateInfo& info)
	{
		m_ImageSampler.CreateSampler(device, info);
	}

	void Image::SetName(const std::string& name)
	{
		DEBUGUTILS_SETOBJECTNAME(m_Image, name + "Image")
		DEBUGUTILS_SETOBJECTNAME(m_ImageView, name + "ImageView")
		DEBUGUTILS_SETOBJECTNAME(m_ImageSampler, name + "ImageSampler")
	}
}