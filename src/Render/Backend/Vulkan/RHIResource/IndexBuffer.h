#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/Buffer.h"
#include "Render/Frontend/RHI/IndexBuffer.h"

namespace PlayGround::Vulkan {

	class IndexBuffer : public ContextAccessor, public RHI::IndexBuffer::Impl
	{
	public:

		IndexBuffer(Context& context) : ContextAccessor(context) {}
		~IndexBuffer() = default;

	private:

		Unit::Buffer m_Buffer;
	};
}