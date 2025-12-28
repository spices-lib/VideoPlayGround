#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace PlayGround::RHI {

	using RHIDescriptorList = RHI<class Descriptor, ERHI::DescriptorList>;

	template<>
	class RHIDescriptorList::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;

		virtual void AddUniformBuffer(uint32_t set, uint32_t binding, uint32_t bytes) = 0;

		virtual void Build() = 0;
	};

	class DescriptorList : public RHIDescriptorList
	{
	public:

		DescriptorList() = default;
		~DescriptorList() override = default;

		void AddUniformBuffer(uint32_t set, uint32_t binding, uint32_t bytes) { m_Impl->AddUniformBuffer(set, binding, bytes); }

		void Build() const { m_Impl->Build(); }
	};
}