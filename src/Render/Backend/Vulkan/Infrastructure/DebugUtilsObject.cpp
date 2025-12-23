#include "DebugUtilsObject.h"
#include "Functions.h"
#include "Device.h"

namespace PlayGround::Vulkan {

	DebugUtilsObject::DebugUtilsObject(Context& context)
        : Infrastructure(context)
    {}

	void DebugUtilsObject::BeginLabel(VkCommandBuffer cmdBuffer, const std::string& caption, glm::vec4 color)
	{
		VkDebugUtilsLabelEXT             labelInfo{};
		labelInfo.sType                = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
		labelInfo.pLabelName           = caption.c_str();

		memcpy(labelInfo.color, &color[0], sizeof(float) * 4);

		m_Context.Get<Functions>()->vkCmdBeginDebugUtilsLabelEXT(cmdBuffer, &labelInfo);
	}

	void DebugUtilsObject::EndLabel(VkCommandBuffer cmdBuffer)
	{
		m_Context.Get<Functions>()->vkCmdEndDebugUtilsLabelEXT(cmdBuffer);
	}

	void DebugUtilsObject::InsertLabel(VkCommandBuffer cmdBuffer, const std::string& caption, glm::vec4 color)
	{
		VkDebugUtilsLabelEXT         labelInfo{};
		labelInfo.sType            = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
		labelInfo.pLabelName       = caption.c_str();

		memcpy(labelInfo.color, &color[0], sizeof(float) * 4);

		m_Context.Get<Functions>()->vkCmdInsertDebugUtilsLabelEXT(cmdBuffer, &labelInfo);
	}

	void DebugUtilsObject::BeginQueueLabel(VkQueue queue, const std::string& caption, glm::vec4 color)
	{
		VkDebugUtilsLabelEXT        labelInfo{};
		labelInfo.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
		labelInfo.pLabelName      = caption.c_str();

		memcpy(labelInfo.color, &color[0], sizeof(float) * 4);

		m_Context.Get<Functions>()->vkQueueBeginDebugUtilsLabelEXT(queue, &labelInfo);
	}

	void DebugUtilsObject::EndQueueLabel(VkQueue queue)
	{
		m_Context.Get<Functions>()->vkQueueEndDebugUtilsLabelEXT(queue);
	}

	void DebugUtilsObject::InsertQueueLabel(VkQueue queue, const std::string& caption, glm::vec4 color)
	{
		VkDebugUtilsLabelEXT        labelInfo{};
		labelInfo.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
		labelInfo.pLabelName      = caption.c_str();

		memcpy(labelInfo.color, &color[0], sizeof(float) * 4);

		m_Context.Get<Functions>()->vkQueueInsertDebugUtilsLabelEXT(queue, &labelInfo);
	}

	void DebugUtilsObject::SetObjectName(VkObjectType type, uint64_t handle, const std::string& caption)
	{
		VkDebugUtilsObjectNameInfoEXT       name_info{};
		name_info.sType                   = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
		name_info.objectType              = type;
		name_info.objectHandle            = handle;
		name_info.pObjectName             = caption.c_str();

		VK_CHECK(m_Context.Get<Functions>()->vkSetDebugUtilsObjectNameEXT(m_Context.Get<Device>()->Handle(), &name_info))
	}

	void DebugUtilsObject::SetObjectTag(VkObjectType type, uint64_t handle, const std::vector<char*>& captions)
	{
		VkDebugUtilsObjectTagInfoEXT    tag_info{};
		tag_info.sType                = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT;
		tag_info.objectType           = type;
		tag_info.objectHandle         = handle;
		tag_info.tagName              = 0;
		tag_info.tagSize              = captions.size();
		tag_info.pTag                 = captions.data();

		VK_CHECK(m_Context.Get<Functions>()->vkSetDebugUtilsObjectTagEXT(m_Context.Get<Device>()->Handle(), &tag_info))
	}
}