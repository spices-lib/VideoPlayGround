#include "SlatePass.h"
#include "Render/Frontend/RHI/Descriptor.h"
#include "Render/Frontend/RHI/Pipeline.h"
#include "Render/Frontend/RHI/RenderPass.h"

namespace PlayGround::Render {

	void SlatePass::OnConstruct()
	{
		/*m_RenderPass = CreateSP<RHI::RenderPass>();
		m_RenderPass->AddSwapChainAttachment();
		m_RenderPass->Build();

		m_Descriptor = CreateSP<RHI::Descriptor>();
		m_Descriptor->Build();

		m_Pipeline = CreateSP<RHI::Pipeline>();
		m_Pipeline->SetDefault();
		m_Pipeline->SetRenderPass(m_RenderPass);
		m_Pipeline->SetDescriptor(m_Descriptor);
		m_Pipeline->SetCullMode(CullMode::None);
		m_Pipeline->SetShaders();
		m_Pipeline->Build();*/
	}

	void SlatePass::OnRender(Scene* scene)
	{

	}
}