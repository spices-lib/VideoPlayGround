#include "CmdList.h"
#include "Render/Backend/Vulkan/Infrastructure/Context.h"
#include "Render/Backend/Vulkan/Infrastructure/CommandBuffer.h"
#include "Render/Backend/Vulkan/RHIResource/RenderPass.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Render/Frontend/RHI/RenderPass.h"
#include "World/Scene/Scene.h"
#include "World/Component/ClockComponent.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <backends/imgui_impl_vulkan.h>
#include <backends/imgui_impl_glfw.h>

namespace PlayGround::Vulkan {

	void CmdList::SetGraphicCmdList(PlayGround::Scene* scene)
	{
		m_Scene = scene;

		const auto& clock = m_Scene->GetComponent<ClockComponent>(m_Scene->GetRoot()).GetClock();

		m_CommandBuffer = GetContext().Get<IGraphicCommandBuffer>()->IHandle(clock.m_FrameIndex);
	}

	void CmdList::CmdDrawSlate() const
	{
		const ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), m_CommandBuffer->GetHandle());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
	}

	void CmdList::CmdBeginRenderPass() const
	{
		const auto& clock = m_Scene->GetComponent<ClockComponent>(m_Scene->GetRoot()).GetClock();

		m_RenderPass->BeginRenderPass(*m_CommandBuffer, clock.m_ImageIndex);
	}

	void CmdList::CmdEndRenderPass() const
	{
		m_CommandBuffer->EndRenderPass();
	}

	void CmdList::CmdBindDescriptor() const
	{

	}

	void CmdList::CmdBindPipeline() const
	{

	}

	void CmdList::CmdDrawFullScreenTriangle() const
	{

	}

	void CmdList::SetRenderPass(SP<RHI::RenderPass> renderPass)
	{
		m_RenderPass = renderPass->GetRHIImpl<RenderPass>();
	}
}