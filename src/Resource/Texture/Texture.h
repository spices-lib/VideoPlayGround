#pragma once
#include "Core/Core.h"
#include <vector>

namespace PlayGround {

	enum class TextureDomain : uint8_t
	{
		Texture1D = 0,
		Texture2D,
		Texture3D,

		Texture1DArray,
		Texture2DArray,

		Count
	};

	enum class TextureFormat : uint16_t
	{
		RGBA8_UNORM = 0,
		RGBA16_SFLOAT,

		Count
	};
}