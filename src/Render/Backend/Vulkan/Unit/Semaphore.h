#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class Semaphore : public Unit<VkSemaphore, VkObjectType::VK_OBJECT_TYPE_SEMAPHORE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		Semaphore() : Unit() {}

		~Semaphore() override;

		void CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo& info);

	private:

		VkDevice m_Device = VK_NULL_HANDLE;
	};
}