#include "SlatePass.h"
#include "Render/Frontend/RHI/Descriptor.h"
#include "Render/Frontend/RHI/Pipeline.h"
#include "Render/Frontend/RHI/RenderPass.h"
#include "Render/Frontend/RHI/CmdList.h"

namespace PlayGround::Render {

	void SlatePass::OnConstruct()
	{
		m_RenderPass = CreateSP<RHI::RenderPass>();
		m_RenderPass->AddSwapChainAttachment();
		m_RenderPass->Build();
	}

	void SlatePass::OnRender(Scene* scene)
	{
		m_CmdList = CreateSP<RHI::CmdList>();

		m_CmdList->SetGraphicCmdList(scene);

		m_CmdList->SetRenderPass(m_RenderPass);

		m_CmdList->CmdBeginRenderPass();

		m_CmdList->CmdDrawSlate();

		m_CmdList->CmdEndRenderPass();
	}
}