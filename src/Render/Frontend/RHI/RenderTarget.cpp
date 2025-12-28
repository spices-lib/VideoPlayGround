#include "RenderTarget.h"
#include "Resource/Texture/RenderTarget.h"

namespace PlayGround::RHI {

	void RenderTarget::CreateRenderTarget(RenderTargetCreateInfo& info)
	{
		m_Format   = info.format;
		m_Domain   = info.domain;
		m_Width    = info.width;
		m_Height   = info.height;

		m_Impl->CreateRenderTarget(info);
	}
}