#pragma once
#include "Core/Core.h"
#include "Pass.h"

namespace PlayGround::RHI {

	class RenderPass;
	class Pipeline;
	class Descriptor;
	class CmdList;
	class RenderTarget;
}

namespace PlayGround::Render { 

	class BasePass : public Pass
	{
	public:

		BasePass() : Pass() {}
		~BasePass() override = default;

		void OnConstruct() override;

		void OnRender(Scene* scene) override;

	private:

		SP<RHI::RenderPass>      m_RenderPass;
		SP<RHI::Descriptor>      m_Descriptor;
		SP<RHI::Pipeline>        m_Pipeline;
		SP<RHI::CmdList>         m_CmdList;
		SP<RHI::RenderTarget>    m_SceneRT;
		
	};
}