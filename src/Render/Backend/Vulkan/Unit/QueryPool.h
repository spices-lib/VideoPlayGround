#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class QueryPool : public Unit<VkQueryPool, VkObjectType::VK_OBJECT_TYPE_QUERY_POOL>
	{
	public:

		using Handle = Unit::Handle;

	public:

		QueryPool() : Unit() {}

		~QueryPool() override;

		void CreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo& info);

	private:

		VkDevice         m_Device = VK_NULL_HANDLE;
	};
}