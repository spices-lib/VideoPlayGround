#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace PlayGround::RHI {

	using RHIPipeline = RHI<class Pipeline, ERHI::Pipeline>;

	template<>
	class RHIPipeline::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;

		virtual void SetDefault() = 0;
		virtual void SetRenderPass() = 0;
		virtual void SetDescriptor() = 0;
		virtual void SetCullMode() = 0;
		virtual void SetShaders() = 0;
		virtual void Build() = 0;
	};

	class Pipeline : public RHIPipeline
	{
	public:

		Pipeline() = default;
		~Pipeline() override = default;

		void SetDefault() const { m_Impl->SetDefault(); }
		void SetRenderPass() const { m_Impl->SetRenderPass(); }
		void SetDescriptor() const { m_Impl->SetDescriptor(); }
		void SetCullMode() const { m_Impl->SetCullMode(); }
		void SetShaders() const { m_Impl->SetShaders(); }
		void Build() const { m_Impl->Build(); }

	};

	
}