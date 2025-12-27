#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Frontend/Pass/Pass.h"

namespace PlayGround::Vulkan {

	class Pass : public Render::Pass::Impl
	{
	public:

		Pass() = default;
		~Pass() override = default;

	private:

	};
}