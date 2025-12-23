#include "Infrastructure.h"

namespace PlayGround::Vulkan {

	Infrastructure::Infrastructure(Context& context)
		: m_Context(context)
	{}

	Infrastructure::~Infrastructure()
	{
		Destroy(this);
	}

}