#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/Image.h"
#include "Render/Backend/Vulkan/Unit/ImageView.h"
#include "Render/Backend/Vulkan/Unit/Sampler.h"
#include "Render/Frontend/RHI/RenderTarget.h"

namespace PlayGround::Vulkan {

	class RenderTarget : public ContextAccessor, public RHI::RenderTarget::Impl
	{
	public:

		RenderTarget(Context& context) : ContextAccessor(context) {}
		~RenderTarget() = default;

	private:

		Unit::Image m_Image;
		Unit::ImageView m_ImageView;
		Unit::Sampler m_ImageSampler;
	};
}