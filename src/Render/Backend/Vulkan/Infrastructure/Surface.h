#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Render/Backend/Vulkan/Infrastructure/Instance.h"
#include "Render/Backend/Vulkan/Unit/Surface.h"

namespace PlayGround::Vulkan {

	using ISurface = InfrastructureClass<class Surface, EInfrastructure::Surface>;

	class Surface : public Infrastructure
	{
	public:

		Surface(Context& context, EInfrastructure e);

		~Surface() override = default;

		const VkSurfaceKHR& Handle() { return m_Surface.GetHandle(); }

	private:

		void Create();

	private:

		Unit::Surface m_Surface;

	};
	
}