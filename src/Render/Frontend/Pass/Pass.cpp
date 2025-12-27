#include "Pass.h"
#include "Render/Backend/Vulkan/Pass/Pass.h"

namespace PlayGround::Render { 

	Pass::Pass()
	{
		m_Impl = CreatePassImplement();
	}

	void Pass::OnRender(Scene* scene)
	{
		m_Impl->OnRender(scene);
	}

	SP<Pass::Impl> Pass::CreatePassImplement()
	{
		return CreateSP<Vulkan::Pass>();
	}
}