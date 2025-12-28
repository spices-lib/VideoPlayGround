#pragma once
#include "Core/Core.h"
#include "Pass.h"

namespace PlayGround::RHI {

	class DescriptorList;
	class CmdList;
}

namespace PlayGround::Render {

	class PrePass : public Pass
	{
	public:

		PrePass() : Pass() {}
		~PrePass() override = default;

		void OnConstruct() override;

		void OnRender(Scene* scene) override;

	private:

		SP<RHI::DescriptorList>  m_DescriptorList;
		SP<RHI::CmdList>         m_CmdList;

	};
}