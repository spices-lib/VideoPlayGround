#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/VideoSession.h"
#include "Render/Backend/Vulkan/Unit/VideoSessionParameters.h"
#include <array>

namespace PlayGround::Vulkan {

	constexpr uint32_t MAX_BOUND_MEMORY = 16;

	class VideoSession : public ContextAccessor
	{
	public:

		VideoSession(Context& context);
		~VideoSession() override = default;

		const VkVideoSessionKHR& Handle() const { return m_VideoSession.GetHandle(); }

		const VkVideoSessionParametersKHR& Parameters() const { return m_VideoSessionParameters.GetHandle(); }

		void CreateVideoSession();

		void CreateVideoSessionParameters();

		void UpdateVideoSessionParameters();

	private:

		Unit::VideoSession                              m_VideoSession;
		std::array<VkDeviceMemory, MAX_BOUND_MEMORY>    m_Memories{};
		Unit::VideoSessionParameters                    m_VideoSessionParameters;
	};
}