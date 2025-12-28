#include "Image.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Render/Backend/Vulkan/Infrastructure/MemoryAllocator.h"
#include "Render/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Render/Backend/Vulkan/Infrastructure/Device.h"

namespace PlayGround::Vulkan {

	void Image::SetImage(VkImage image)
	{
		m_Image.SetHandle(image);

		DEBUGUTILS_SETOBJECTNAME(m_Image, "Image")
	}

	void Image::CreateImage(const VkImageCreateInfo& info, VkMemoryPropertyFlags properties)
	{
		if (GetContext().Has<IMemoryAllocator>())
		{
			m_Image.CreateImage(GetContext().Get<IMemoryAllocator>()->Handle(), info, properties);
		}
		else
		{
			m_Image.CreateImage(GetContext().Get<IPhysicalDevice>()->Handle(), GetContext().Get<IDevice>()->Handle(), info, properties);
		}

		DEBUGUTILS_SETOBJECTNAME(m_Image, "Image")
	}

	void Image::CreateImageView(VkImageViewCreateInfo& info)
	{
		assert(m_Image.GetHandle());

		info.image = m_Image.GetHandle();

		m_ImageView.CreateImageView(GetContext().Get<IDevice>()->Handle(), info);

		DEBUGUTILS_SETOBJECTNAME(m_ImageView, "ImageView")
	}

	void Image::CreateSampler(VkSamplerCreateInfo& info)
	{
		m_ImageSampler.CreateSampler(GetContext().Get<IDevice>()->Handle(), info);

		DEBUGUTILS_SETOBJECTNAME(m_ImageSampler, "ImageSampler")
	}

	void Image::SetName(const std::string& name) const
	{
		DEBUGUTILS_SETOBJECTNAME(m_Image, name + "Image")
		DEBUGUTILS_SETOBJECTNAME(m_ImageView, name + "ImageView")
		DEBUGUTILS_SETOBJECTNAME(m_ImageSampler, name + "ImageSampler")
	}
}