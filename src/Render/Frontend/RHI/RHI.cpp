#include "RHI.h"

namespace PlayGround::RHI {

	namespace {
	
		RHIDelegate::Creator s_Creator;
	}

	void RHIDelegate::SetCreator(const RHIDelegate::Creator& fn)
	{
		s_Creator = fn;
	}

	const RHIDelegate::Creator& RHIDelegate::GetCreator()
	{
		return s_Creator;
	}
}