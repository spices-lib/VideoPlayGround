#pragma once
#include "Core/Core.h"

namespace PlayGround::Slate {

	class SlateScope
	{
	public:

		static void BeginScope();

		static void EndScope();
	};
}