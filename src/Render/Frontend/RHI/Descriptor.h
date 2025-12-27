#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace PlayGround::RHI {

	using RHIDescriptor = RHI<class Descriptor, ERHI::Descriptor>;

	template<>
	class RHIDescriptor::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;

		virtual void Build() = 0;
	};

	class Descriptor : public RHIDescriptor
	{
	public:

		Descriptor() = default;
		~Descriptor() override = default;

		void Build() const { m_Impl->Build(); }
	};
}