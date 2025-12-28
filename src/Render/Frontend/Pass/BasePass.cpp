#include "BasePass.h"
#include "Render/Frontend/RHI/Pipeline.h"
#include "Render/Frontend/RHI/RenderPass.h"
#include "Render/Frontend/RHI/Descriptor.h"
#include "Render/Frontend/RHI/CmdList.h"
#include "Render/Frontend/RHI/RenderTarget.h"
#include "Resource/Texture/RenderTarget.h"
#include "Resource/Mesh/Mesh.h"

namespace PlayGround::Render {

	void BasePass::OnConstruct()
	{
		RenderTargetCreateInfo    info{};
		info.name               = "Scene";
		info.format             = TextureFormat::RGBA16_SFLOAT;
		info.domain             = TextureDomain::Texture2D;

		m_SceneRT = CreateSP<RHI::RenderTarget>();
		m_SceneRT->CreateRenderTarget(info);

		m_RenderPass = CreateSP<RHI::RenderPass>();
		m_RenderPass->AddColorAttachment(m_SceneRT);
		m_RenderPass->Build();
		
		m_Descriptor = CreateSP<RHI::Descriptor>();
		m_Descriptor->Build();

		m_Pipeline = CreateSP<RHI::Pipeline>();
		m_Pipeline->SetDefault();
		m_Pipeline->SetRenderPass(m_RenderPass);
		m_Pipeline->SetDescriptor(m_Descriptor);
		m_Pipeline->SetCullMode(CullMode::None);
		m_Pipeline->SetShaders();
		m_Pipeline->Build();
	}

	void BasePass::OnRender(Scene* scene)
	{
		m_CmdList = CreateSP<RHI::CmdList>();

		m_CmdList->SetGraphicCmdList(scene);

		m_CmdList->SetRenderPass(m_RenderPass);

		m_CmdList->CmdBeginRenderPass();

		m_CmdList->CmdBindDescriptor();

		m_CmdList->CmdBindPipeline();

		m_CmdList->CmdDrawFullScreenTriangle();

		m_CmdList->CmdEndRenderPass();
	}

}