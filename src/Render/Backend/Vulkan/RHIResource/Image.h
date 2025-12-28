#pragma once
#include "Core/Core.h"
#include "Render/Backend/Vulkan/Core.h"
#include "Render/Backend/Vulkan/Unit/Image.h"
#include "Render/Backend/Vulkan/Unit/ImageView.h"
#include "Render/Backend/Vulkan/Unit/Sampler.h"

namespace PlayGround::Vulkan {

	class Image : public ContextAccessor
	{
	public:

		Image(Context& context) : ContextAccessor(context) {}
		~Image() override = default;

		void SetImage(VkImage image);

		void CreateImage(const VkImageCreateInfo& info, VkMemoryPropertyFlags properties);

		void CreateImageView(VkImageViewCreateInfo& info);

		void CreateSampler(VkSamplerCreateInfo& info);

		void SetName(const std::string& name) const;

		const VkImageView& GetView() const { return m_ImageView.GetHandle(); }

	private:

		Unit::Image m_Image;
		Unit::ImageView m_ImageView;
		Unit::Sampler m_ImageSampler;
	};
}