#include "PrePass.h"
#include "Render/Frontend/RHI/Pipeline.h"
#include "Render/Frontend/RHI/RenderPass.h"
#include "Render/Frontend/RHI/DescriptorList.h"
#include "Render/Frontend/RHI/CmdList.h"
#include "Render/Frontend/RHI/RenderTarget.h"
#include "Resource/Texture/RenderTarget.h"
#include "Resource/Mesh/Mesh.h"
#include "Assets/Shader/Header/ShaderCommon.h"

namespace PlayGround::Render {

	void PrePass::OnConstruct()
	{
		m_DescriptorList = CreateSP<RHI::DescriptorList>();
		m_DescriptorList->AddUniformBuffer(0, 0, sizeof(Shader::View));
		m_DescriptorList->AddUniformBuffer(0, 1, sizeof(Shader::Input));
		m_DescriptorList->Build();
	}

	void PrePass::OnRender(Scene* scene)
	{
		m_CmdList = CreateSP<RHI::CmdList>();

		m_CmdList->SetGraphicCmdList(scene);

		/*m_CmdList->UpdateUniformBuffer<Shader::View>(0, 0, [&](auto& ubo) {
			auto [invViewMatrix, projectionMatrix, stableFrames, fov] = GetActiveCameraMatrix(frameInfo);
			ImVec2 sceneTextureSize = SlateSystem::GetRegister()->GetViewPort()->GetPanelSize();
			const VkExtent2D windowSize = m_Device->GetSwapChainSupport().surfaceSize;

			ubo.projection = projectionMatrix;

			ubo.nprojection = projectionMatrix;
			ubo.nprojection[1][1] *= -1.0f;

			ubo.view = glm::inverse(invViewMatrix);

			ubo.inView = invViewMatrix;

			ubo.sceneTextureSize = {
				sceneTextureSize.x,
				sceneTextureSize.y,
				1.0f / sceneTextureSize.x,
				1.0f / sceneTextureSize.y
			};

			ubo.windowSize = {
				static_cast<float>(windowSize.width),
				static_cast<float>(windowSize.height),
				1.0f / static_cast<float>(windowSize.width),
				1.0f / static_cast<float>(windowSize.height)
			};

			ubo.stableFrames = stableFrames;

			ubo.fov = fov;
		});

		m_CmdList->UpdateUniformBuffer<Shader::View>(0, 0, [&](auto& ubo) {
			auto [x, y] = SlateSystem::GetRegister()->GetViewPort()->GetMousePosInViewport();

			ubo.gameTime = ts.gt();
			ubo.frameTime = ts.ft();
			ubo.mousePos = glm::vec4(
				static_cast<float>(x),
				static_cast<float>(y),
				1.0f / static_cast<float>(x),
				1.0f / static_cast<float>(y)
			);
		});*/
	}

}