#pragma once
#include "Core/Core.h"
#include "RHI.h"
#include "Resource/Texture/Texture.h"

namespace PlayGround {

	struct RenderTargetCreateInfo;
}

namespace PlayGround::RHI {
	
	using RHIRenderTarget = RHI<class RenderTarget, ERHI::RenderTarget>;

	template<>
	class RHIRenderTarget::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;

		virtual void CreateRenderTarget(RenderTargetCreateInfo& info) = 0;
	};

	class RenderTarget : public RHIRenderTarget
	{
	public:

		RenderTarget() = default;
		~RenderTarget() override = default;

		void CreateRenderTarget(RenderTargetCreateInfo& info);

		TextureFormat GetFormat() const { return m_Format; }

		TextureDomain GetDomain() const { return m_Domain; }

		uint32_t GetWidth() const { return m_Width; }

		uint32_t GetHeight() const { return m_Height; }

	protected:

		TextureFormat m_Format;
		TextureDomain m_Domain;
		uint32_t      m_Width;
		uint32_t      m_Height;
	};
}