#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Utils.h"
#include "Render/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include <assert.h>

namespace PlayGround::Vulkan::Unit {

	template<typename Handle, VkObjectType E>
	class Unit
	{
	public:

		static constexpr EUnit s_EUnit = E;

		using Handle = Handle;

	public:

		Unit() = default;

		virtual ~Unit() { ResetHandle(); }

		const EUnit& GetEUnit() const { return s_EUnit; }

		void SetHandle(const Handle& handle) { assert(handle); m_Handle = handle; }

		const Handle& GetHandle() const { return m_Handle; }

		void ResetHandle() { m_Handle = nullptr; }

		void SetName(DebugUtilsObject* debugObject, const std::string& name)
		{
			assert(debugObject && m_Handle);

			debugObject->SetObjectName(s_EUnit, reinterpret_cast<uint64_t>(m_Handle), name);
		}

	protected:

		Handle m_Handle = nullptr;
	};
}