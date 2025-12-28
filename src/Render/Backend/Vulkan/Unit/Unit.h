#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include <assert.h>

namespace PlayGround::Vulkan::Unit {

	template<typename H, VkObjectType E_>
	class Unit
	{
	public:

		static constexpr VkObjectType E = E_;

		using Handle = H;

	public:

		Unit() = default;

		virtual ~Unit() { ResetHandle(); }

		static const VkObjectType& GetEUnit() { return E; }

		void SetHandle(const Handle& handle) { assert(handle); m_Handle = handle; }

		const Handle& GetHandle() const { return m_Handle; }

		void ResetHandle() { m_Handle = nullptr; }

	protected:

		Handle m_Handle = nullptr;
	};
}