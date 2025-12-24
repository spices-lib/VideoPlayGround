#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class Image : public Unit<VkImage, VkObjectType::VK_OBJECT_TYPE_IMAGE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		Image() : Unit() {}

		~Image() override = default;
	};
}