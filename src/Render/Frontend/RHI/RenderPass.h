#pragma once
#include "Core/Core.h"
#include "RHI.h"
#include <any>

namespace PlayGround::RHI {
	
	using RHIRenderPass = RHI<class RenderPass, ERHI::RenderPass>;

	template<>
	class RHIRenderPass::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;

		virtual void AddSwapChainAttachment() = 0;

		virtual void AddColorAttachment(SP<class RenderTarget> renderTarget) = 0;

		virtual void Build() = 0;
	};

	class RenderPass : public RHIRenderPass
	{
	public:

		RenderPass() = default;
		~RenderPass() override = default;
		
		void AddSwapChainAttachment() const { m_Impl->AddSwapChainAttachment(); }

		void AddColorAttachment(SP<class RenderTarget> renderTarget) const { m_Impl->AddColorAttachment(renderTarget); }

		void Build() const { m_Impl->Build(); }

	};
}