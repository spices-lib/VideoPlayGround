#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Render/Backend/Vulkan/Infrastructure/Instance.h"

namespace PlayGround::Vulkan {

	class Surface : public Infrastructure
	{
	public:

		static constexpr EInfrastructure Type = EInfrastructure::Surface;

	public:

		Surface(Context& context);

		~Surface() override = default;

		VkSurfaceKHR& Handle() { return m_Handle; }

	private:

		void Create();

	private:

		VkSurfaceKHR m_Handle = nullptr;

	};

	template<>
	inline void Infrastructure::Destroy(Surface* infrastructure)
	{
		const auto instance = infrastructure->m_Context.Get<Instance>()->Handle();

		vkDestroySurfaceKHR(instance, infrastructure->Handle(), nullptr);
		infrastructure->Handle() = nullptr;
	}

}