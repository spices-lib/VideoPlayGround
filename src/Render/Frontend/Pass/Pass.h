#pragma once
#include "Core/Core.h"

namespace PlayGround {

	class Scene;
}

namespace PlayGround::Render { 

	class Pass
	{
	public:

		Pass() = default;
		virtual ~Pass() = default;

		virtual void OnConstruct() = 0;

		virtual void OnRender(Scene* scene) = 0;
	};
}