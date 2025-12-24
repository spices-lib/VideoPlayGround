#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class ImageView : public Unit<VkImageView, VkObjectType::VK_OBJECT_TYPE_IMAGE_VIEW>
	{
	public:

		using Handle = Unit::Handle;

	public:

		ImageView() : Unit() {}

		~ImageView() override;

		void CreateImageView(VkDevice device, const VkImageViewCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;
	};
}