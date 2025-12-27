#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/Shader.h"
#include "Render/Frontend/RHI/Shader.h"

namespace PlayGround::Vulkan {

	class Shader : public ContextAccessor, public RHI::Shader::Impl
	{
	public:

		Shader(Context& context) : ContextAccessor(context) {}
		~Shader() = default;

	private:

		Unit::Shader m_Shader;
	};
}