#include "Core/Core.h"
#include "Render/Backend/Vulkan/Infrastructure/ContextAccessor.h"
#include "Render/Backend/Vulkan/Utils.h"
#include "Render/Backend/Vulkan/Unit/Image.h"
#include "Render/Backend/Vulkan/Unit/ImageView.h"
#include "Render/Backend/Vulkan/Unit/Sampler.h"

namespace PlayGround::Vulkan {

	class Image : public ContextAccessor
	{
	public:

		Image(Context& context) : ContextAccessor(context) {}
		~Image() = default;

		void SetImage(VkImage image);
		void CreateImageView(VkDevice device, VkImageViewCreateInfo& info);
		void CreateSampler(VkDevice device, VkSamplerCreateInfo& info);
		void SetName(const std::string& name);

	private:

		Unit::Image m_Image;
		Unit::ImageView m_ImageView;
		Unit::Sampler m_ImageSampler;
	};
}