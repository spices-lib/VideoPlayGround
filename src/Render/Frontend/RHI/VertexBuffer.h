#pragma once
#include "Core/Core.h"
#include "RHI.h"

namespace PlayGround::RHI {
	
	using RHIVertexBuffer = RHI<class VertexBuffer, ERHI::VertexBuffer>;

	template<>
	class RHIVertexBuffer::Impl
	{
	public:

		Impl() = default;
		virtual ~Impl() = default;
	};

	class VertexBuffer : public RHIVertexBuffer
	{
	public:

		VertexBuffer() = default;
		~VertexBuffer() override = default;

	};
}