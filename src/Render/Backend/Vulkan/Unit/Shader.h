#pragma once
#include "Core/Core.h"
#include "Unit.h"

namespace PlayGround::Vulkan::Unit {

	class Shader : public Unit<VkShaderModule, VkObjectType::VK_OBJECT_TYPE_SHADER_MODULE>
	{
	public:

		using Handle = Unit::Handle;

	public:

		Shader() : Unit() {}

		~Shader() override;

		void CreateShader(VkDevice device, const VkShaderModuleCreateInfo& info);

	private:

		VkDevice         m_Device = VK_NULL_HANDLE;
	};
}