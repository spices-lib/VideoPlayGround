#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace PlayGround::RHI {
	
	using RHIShader = RHI<class Shader, ERHI::Shader>;

	template<>
	class RHIShader::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;
	};

	class Shader : public RHIShader
	{
	public:

		Shader() = default;
		~Shader() override = default;

	};
}