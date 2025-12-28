#pragma once
#include "Core/Core.h"
#include "Resource/Mesh/Mesh.h"
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
		virtual void SetRenderPass(SP<class RenderPass> renderPass) = 0;
		virtual void SetDescriptor(SP<class Descriptor> descriptor) = 0;
		virtual void SetCullMode(CullMode mode) = 0;
		virtual void SetShaders() = 0;
		virtual void Build() = 0;
	};

	class Pipeline : public RHIPipeline
	{
	public:

		Pipeline() = default;
		~Pipeline() override = default;

		void SetDefault() const { m_Impl->SetDefault(); }
		void SetRenderPass(SP<class RenderPass> renderPass) const { m_Impl->SetRenderPass(renderPass); }
		void SetDescriptor(SP<class Descriptor> descriptor) const { m_Impl->SetDescriptor(descriptor); }
		void SetCullMode(CullMode mode) const { m_Impl->SetCullMode(mode); }
		void SetShaders() const { m_Impl->SetShaders(); }
		void Build() const { m_Impl->Build(); }

	};

	
}