#include "Pass.h"
#include "Render/Backend/Vulkan/Pass/Pass.h"

namespace PlayGround::Render { 

	Pass::Pass()
	{
		m_Impl = CreatePassImplement();
	}

	SP<Pass::Impl> Pass::CreatePassImplement()
	{
		return CreateSP<Vulkan::Pass>();
	}
}