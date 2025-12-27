#pragma once
#include "Core/Core.h"
#include "Pass.h"
#include <functional>

namespace PlayGround::RHI {

	class RenderPass;
	class Pipeline;
	class Descriptor;
	class CmdList;
}

namespace PlayGround::Render {

	class SlatePass : public Pass
	{
	public:

		SlatePass() : Pass() {}
		~SlatePass() override = default;

		void OnConstruct() override;

		void OnRender(Scene* scene) override;

		SP<RHI::RenderPass> GetRenderPass() { return m_RenderPass; }

	private:

		SP<RHI::RenderPass> m_RenderPass;
		SP<RHI::CmdList>    m_CmdList;
	};
}