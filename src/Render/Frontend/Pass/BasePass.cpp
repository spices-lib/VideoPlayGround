#include "BasePass.h"
#include "Render/Frontend/RHI/Pipeline.h"
#include "Render/Frontend/RHI/RenderPass.h"
#include "Render/Frontend/RHI/Descriptor.h"

namespace PlayGround::Render {

	void BasePass::OnConstruct()
	{
		/*m_RenderPass = CreateSP<RHI::RenderPass>();
		m_RenderPass->AddColorAttachment("Scene", TextureType::Texture2D, TextureFormat::RGBA16);
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

	void BasePass::OnRender(Scene* scene)
	{
		/*BeginRenderPass();

		BindDescriptor();

		BindPipeline();

		DrawFullScreenTriangle();

		EndRenderPass();*/
	}

}