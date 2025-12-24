#include "Infrastructure.h"
#include "Instance.h"
#include "Functions.h"

namespace PlayGround::Vulkan {

	Infrastructure::Infrastructure(Context& context, EInfrastructure e)
		: ContextAccessor(context)
		, m_EInfrastructure(e)
	{}
}