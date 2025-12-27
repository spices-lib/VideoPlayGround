#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace PlayGround::RHI {
	
	using RHIRenderTarget = RHI<class RenderTarget, ERHI::RenderTarget>;

	template<>
	class RHIRenderTarget::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;
	};

	class RenderTarget : public RHIRenderTarget
	{
	public:

		RenderTarget() = default;
		~RenderTarget() override = default;

	};
}