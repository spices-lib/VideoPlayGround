#pragma once
#include "Core/Core.h"
#include "Texture.h"

namespace PlayGround {

	enum class RHIMemoryUsage
	{
		Device = 0,
		Host,
		Shared,
		Preserved,
	};

	struct RenderTargetCreateInfo
	{
		std::string       name         = "";
		uint32_t          width        = 100;
		uint32_t          height       = 100;
		TextureDomain     domain       = TextureDomain::Texture2D;
		TextureFormat     format       = TextureFormat::RGBA8_UNORM;
		RHIMemoryUsage    memoryUsage  = RHIMemoryUsage::Device;
	};
}