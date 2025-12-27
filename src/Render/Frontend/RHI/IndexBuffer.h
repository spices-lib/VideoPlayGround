#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace PlayGround::RHI {
	
	using RHIIndexBuffer = RHI<class IndexBuffer, ERHI::IndexBuffer>;

	template<>
	class RHIIndexBuffer::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;
	};

	class IndexBuffer : public RHIIndexBuffer
	{
	public:

		IndexBuffer() = default;
		~IndexBuffer() override = default;

	};
}