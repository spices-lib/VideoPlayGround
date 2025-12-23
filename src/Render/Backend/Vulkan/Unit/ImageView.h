#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class ImageView : public Unit<VkImageView, VkObjectType::VK_OBJECT_TYPE_IMAGE_VIEW>
	{
	public:

		using Handle = Unit::Handle;

	public:

		ImageView(Handle handle) : Unit(handle) {}

		~ImageView() override = default;
	};
}