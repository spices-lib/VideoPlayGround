#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include "Functions.h"
#include "Device.h"
#include <glm/glm.hpp>
#include <vector>

namespace PlayGround::Vulkan {

	using IDebugUtilsObject = InfrastructureClass<class DebugUtilsObject, EInfrastructure::DebugUtilsObject>;

	class DebugUtilsObject : public Infrastructure
	{
	public:

		DebugUtilsObject(Context& context, EInfrastructure e);

		~DebugUtilsObject() override = default;

		void BeginLabel(VkCommandBuffer cmdBuffer, const std::string& caption, glm::vec4 color = glm::vec4(1.0f)) const;
		void EndLabel(VkCommandBuffer cmdBuffer) const;
		void InsertLabel(VkCommandBuffer cmdBuffer, const std::string& caption, glm::vec4 color = glm::vec4(1.0f)) const;

		void BeginQueueLabel(VkQueue queue, const std::string& caption, glm::vec4 color = glm::vec4(1.0f)) const;
		void EndQueueLabel(VkQueue queue) const;
		void InsertQueueLabel(VkQueue queue, const std::string& caption, glm::vec4 color = glm::vec4(1.0f)) const;

		template<typename Unit>
		void SetObjectName(const Unit& unit, const std::string& caption);
		
		template<typename Unit>
		void SetObjectTag(const Unit& unit, const std::vector<char*>& captions) const;

	private:

		VkDevice m_Device = VK_NULL_HANDLE;
	};
	
#ifdef PG_DEBUG

#define DEBUGUTILS_BEGINLABEL(...)                 { GetContext().Get<IDebugUtilsObject>()->BeginLabel       (__VA_ARGS__)	; }
#define DEBUGUTILS_ENDLABEL(...)                   { GetContext().Get<IDebugUtilsObject>()->EndLabel         (__VA_ARGS__)	; }
#define DEBUGUTILS_INSERTLABEL(...)                { GetContext().Get<IDebugUtilsObject>()->InsertLabel      (__VA_ARGS__)	; }
#define DEBUGUTILS_BEGINQUEUELABEL(...)            { GetContext().Get<IDebugUtilsObject>()->BeginQueueLabel  (__VA_ARGS__)	; }
#define DEBUGUTILS_ENDQUEUELABEL(...)              { GetContext().Get<IDebugUtilsObject>()->EndQueueLabel    (__VA_ARGS__)	; }
#define DEBUGUTILS_INSERTQUEUELABEL(...)           { GetContext().Get<IDebugUtilsObject>()->InsertQueueLabel (__VA_ARGS__)	; }
#define DEBUGUTILS_SETOBJECTNAME(...)              { GetContext().Get<IDebugUtilsObject>()->SetObjectName    (__VA_ARGS__)	; }
#define DEBUGUTILS_SETOBJECTTAG(...)               { GetContext().Get<IDebugUtilsObject>()->SetObjectTag     (__VA_ARGS__)	; }

#endif

#ifdef PG_RELEASE

#define DEBUGUTILS_BEGINLABEL(...)      
#define DEBUGUTILS_ENDLABEL(...)        
#define DEBUGUTILS_INSERTLABEL(...)     
#define DEBUGUTILS_BEGINQUEUELABEL(...) 
#define DEBUGUTILS_ENDQUEUELABEL(...)   
#define DEBUGUTILS_INSERTQUEUELABEL(...)
#define DEBUGUTILS_SETOBJECTNAME(...)   
#define DEBUGUTILS_SETOBJECTTAG(...)                 

#endif

	template<typename Unit>
	inline void DebugUtilsObject::SetObjectName(const Unit& unit, const std::string& caption)
	{
		VkDebugUtilsObjectNameInfoEXT       name_info{};
		name_info.sType                   = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
		name_info.objectType              = Unit::GetEUnit();
		name_info.objectHandle            = reinterpret_cast<uint64_t>(unit.GetHandle());
		name_info.pObjectName             = caption.c_str();

		VK_CHECK(GetContext().Get<IFunctions>()->vkSetDebugUtilsObjectNameEXT(m_Device, &name_info))
	}

	template<>
	inline void DebugUtilsObject::SetObjectName<Unit::Device>(const Unit::Device& unit, const std::string& caption)
	{
		assert(unit.GetHandle());

		m_Device = unit.GetHandle();
		
		VkDebugUtilsObjectNameInfoEXT       name_info{};
		name_info.sType                   = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
		name_info.objectType              = Unit::Device::GetEUnit();
		name_info.objectHandle            = reinterpret_cast<uint64_t>(unit.GetHandle());
		name_info.pObjectName             = caption.c_str();

		VK_CHECK(GetContext().Get<IFunctions>()->vkSetDebugUtilsObjectNameEXT(unit.GetHandle(), &name_info))
	}
	
	template <typename Unit>
	inline void DebugUtilsObject::SetObjectTag(const Unit& unit, const std::vector<char*>& captions) const
	{
		VkDebugUtilsObjectTagInfoEXT        tag_info{};
		tag_info.sType                    = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT;
		tag_info.objectType               = Unit::GetEUnit();
		tag_info.objectHandle             = reinterpret_cast<uint64_t>(unit.GetHandle());
		tag_info.tagName                  = 0;
		tag_info.tagSize                  = captions.size();
		tag_info.pTag                     = captions.data();
		
		VK_CHECK(GetContext().Get<IFunctions>()->vkSetDebugUtilsObjectTagEXT(m_Device, &tag_info))
	}
}