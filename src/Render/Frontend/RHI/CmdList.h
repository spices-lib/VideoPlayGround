#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace PlayGround {

	class Scene;
}

namespace PlayGround::RHI {

	using RHICmdList = RHI<class Cmds, ERHI::CmdList>;

	template<>
	class RHICmdList::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;

		virtual void SetGraphicCmdList(PlayGround::Scene* scene) = 0;

		virtual void SetRenderPass(SP<class RenderPass> renderPass) = 0;

		virtual void CmdDrawSlate() const = 0;

		virtual void CmdBeginRenderPass() const = 0;

		virtual void CmdEndRenderPass() const = 0;

		virtual void CmdBindDescriptor() const = 0;

		virtual void CmdBindPipeline() const = 0;

		virtual void CmdDrawFullScreenTriangle() const = 0;
	};

	class CmdList : public RHICmdList
	{
	public:

		CmdList() = default;
		~CmdList() override = default;

		void SetGraphicCmdList(PlayGround::Scene* scene) { m_Impl->SetGraphicCmdList(scene); }

		void SetRenderPass(SP<class RenderPass> renderPass) { m_Impl->SetRenderPass(renderPass); }

		void CmdDrawSlate() const { m_Impl->CmdDrawSlate(); }

		void CmdBeginRenderPass() const { m_Impl->CmdBeginRenderPass(); }

		void CmdEndRenderPass() const { m_Impl->CmdEndRenderPass(); }

		void CmdBindDescriptor() const { m_Impl->CmdBindDescriptor(); }

		void CmdBindPipeline() const { m_Impl->CmdBindPipeline(); }

		void CmdDrawFullScreenTriangle() const { m_Impl->CmdDrawFullScreenTriangle(); }
	};
}