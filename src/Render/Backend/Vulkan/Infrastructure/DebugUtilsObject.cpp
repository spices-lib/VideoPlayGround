#include "DebugUtilsObject.h"
#include "Functions.h"
#include "Device.h"

namespace PlayGround::Vulkan {

	DebugUtilsObject::DebugUtilsObject(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {}

	void DebugUtilsObject::BeginLabel(VkCommandBuffer cmdBuffer, const std::string& caption, glm::vec4 color) const
	{
		VkDebugUtilsLabelEXT             labelInfo{};
		labelInfo.sType                = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
		labelInfo.pLabelName           = caption.c_str();

		memcpy(labelInfo.color, &color[0], sizeof(float) * 4);

		GetContext().Get<IFunctions>()->vkCmdBeginDebugUtilsLabelEXT(cmdBuffer, &labelInfo);
	}

	void DebugUtilsObject::EndLabel(VkCommandBuffer cmdBuffer) const
	{
		GetContext().Get<IFunctions>()->vkCmdEndDebugUtilsLabelEXT(cmdBuffer);
	}

	void DebugUtilsObject::InsertLabel(VkCommandBuffer cmdBuffer, const std::string& caption, glm::vec4 color) const
	{
		VkDebugUtilsLabelEXT         labelInfo{};
		labelInfo.sType            = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
		labelInfo.pLabelName       = caption.c_str();

		memcpy(labelInfo.color, &color[0], sizeof(float) * 4);

		GetContext().Get<IFunctions>()->vkCmdInsertDebugUtilsLabelEXT(cmdBuffer, &labelInfo);
	}

	void DebugUtilsObject::BeginQueueLabel(VkQueue queue, const std::string& caption, glm::vec4 color) const
	{
		VkDebugUtilsLabelEXT        labelInfo{};
		labelInfo.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
		labelInfo.pLabelName      = caption.c_str();

		memcpy(labelInfo.color, &color[0], sizeof(float) * 4);

		GetContext().Get<IFunctions>()->vkQueueBeginDebugUtilsLabelEXT(queue, &labelInfo);
	}

	void DebugUtilsObject::EndQueueLabel(VkQueue queue) const
	{
		GetContext().Get<IFunctions>()->vkQueueEndDebugUtilsLabelEXT(queue);
	}

	void DebugUtilsObject::InsertQueueLabel(VkQueue queue, const std::string& caption, glm::vec4 color) const
	{
		VkDebugUtilsLabelEXT        labelInfo{};
		labelInfo.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
		labelInfo.pLabelName      = caption.c_str();

		memcpy(labelInfo.color, &color[0], sizeof(float) * 4);

		GetContext().Get<IFunctions>()->vkQueueInsertDebugUtilsLabelEXT(queue, &labelInfo);
	}
}