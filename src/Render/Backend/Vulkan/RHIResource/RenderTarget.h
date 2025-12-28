#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/RHIResource/Image.h"
#include "Render/Frontend/RHI/RenderTarget.h"

namespace PlayGround::Vulkan {

	class RenderTarget : public ContextAccessor, public RHI::RenderTarget::Impl
	{
	public:

		RenderTarget(Context& context) : ContextAccessor(context), m_Image(context) {}
		~RenderTarget() = default;

		void CreateRenderTarget(RenderTargetCreateInfo& info) override;

		const VkImageView& GetView() const;

	private:

		Image m_Image;
	};
}