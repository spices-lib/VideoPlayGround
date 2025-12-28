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
		virtual void SetDescriptorList(SP<class DescriptorList> descriptorList) = 0;
		virtual void SetVertexAttributeLayout() = 0;
		virtual void SetCullMode(CullMode mode) = 0;
		virtual void SetShaders() = 0;
		virtual void BuildGraphicPipeline() = 0;
	};

	class Pipeline : public RHIPipeline
	{
	public:

		Pipeline() = default;
		~Pipeline() override = default;

		void SetDefault() const { m_Impl->SetDefault(); }
		void SetRenderPass(SP<class RenderPass> renderPass) const { m_Impl->SetRenderPass(renderPass); }
		void SetVertexAttributeLayout() const { m_Impl->SetVertexAttributeLayout(); }
		void SetDescriptorList(SP<class DescriptorList> descriptorList) const { m_Impl->SetDescriptorList(descriptorList); }
		void SetCullMode(CullMode mode) const { m_Impl->SetCullMode(mode); }
		void SetShaders() const { m_Impl->SetShaders(); }
		void BuildGraphicPipeline() const { m_Impl->BuildGraphicPipeline(); }

	};

	
}