#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/CommandBuffer.h"
#include "Render/Frontend/RHI/CmdList.h"

namespace PlayGround {

	class Scene;
}

namespace PlayGround::RHI {

	class RenderPass;
}

namespace PlayGround::Vulkan {

	class RenderPass;

	class CmdList : public ContextAccessor, public RHI::CmdList::Impl
	{
	public:

		CmdList(Context& context) : ContextAccessor(context), RHI::CmdList::Impl() {}
		~CmdList() override = default;

		void SetGraphic(PlayGround::Scene* scene) override;

		void CmdDrawSlate() const override;

		void CmdBeginRenderPass() const override;

		void CmdEndRenderPass() const override;

		void SetRenderPass(SP<RHI::RenderPass> renderPass) override;

	private:

		PlayGround::Scene* m_Scene = nullptr;
		SP<Unit::CommandBuffer> m_CommandBuffer = nullptr;
		SP<Vulkan::RenderPass> m_RenderPass = nullptr;

	};
}