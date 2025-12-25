#include "Core/Core.h"
#include "Render/Backend/Vulkan/Utils.h"
#include "Render/Backend/Vulkan/Unit/RenderPass.h"
#include "Render/Backend/Vulkan/Unit/FrameBuffer.h"
#include <vector>

namespace PlayGround::Vulkan {

	class RenderPass : public ContextAccessor
	{
	public:

		RenderPass(Context& context) : ContextAccessor(context) {}
		~RenderPass() = default;

	private:

		Unit::RenderPass m_RenderPass;
		std::vector<SP<Unit::FrameBuffer>> m_FrameBuffers;
	};
}