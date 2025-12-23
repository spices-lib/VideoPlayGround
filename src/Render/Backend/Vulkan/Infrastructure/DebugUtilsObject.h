#pragma once
#include "Core/Core.h"
#include "Infrastructure.h"
#include <glm/glm.hpp>
#include <vector>

namespace PlayGround::Vulkan {

	class DebugUtilsObject : public Infrastructure
	{
	public:

		static constexpr EInfrastructure Type = EInfrastructure::DebugUtilsObject;

	public:

		DebugUtilsObject(Context& context);

		~DebugUtilsObject() override = default;

		void BeginLabel(VkCommandBuffer cmdBuffer, const std::string& caption, glm::vec4 color = glm::vec4(1.0f));
		void EndLabel(VkCommandBuffer cmdBuffer);
		void InsertLabel(VkCommandBuffer cmdBuffer, const std::string& caption, glm::vec4 color = glm::vec4(1.0f));

		void BeginQueueLabel(VkQueue queue, const std::string& caption, glm::vec4 color = glm::vec4(1.0f));
		void EndQueueLabel(VkQueue queue);
		void InsertQueueLabel(VkQueue queue, const std::string& caption, glm::vec4 color = glm::vec4(1.0f));

		void SetObjectName(VkObjectType type, uint64_t handle, const std::string& caption);
		void SetObjectTag(VkObjectType type, uint64_t handle, const std::vector<char*>& captions);
	};

	template<>
	inline void Infrastructure::Destroy(DebugUtilsObject* infrastructure)
	{}

#ifdef PG_DEBUG

#define DEBUGUTILS_BEGINLABEL(...)                 { m_Context.Get<DebugUtilsObject>()->BeginLabel       (__VA_ARGS__)	; }
#define DEBUGUTILS_ENDLABEL(...)                   { m_Context.Get<DebugUtilsObject>()->EndLabel         (__VA_ARGS__)	; }
#define DEBUGUTILS_INSERTLABEL(...)                { m_Context.Get<DebugUtilsObject>()->InsertLabel      (__VA_ARGS__)	; }
#define DEBUGUTILS_BEGINQUEUELABEL(...)            { m_Context.Get<DebugUtilsObject>()->BeginQueueLabel  (__VA_ARGS__)	; }
#define DEBUGUTILS_ENDQUEUELABEL(...)              { m_Context.Get<DebugUtilsObject>()->EndQueueLabel    (__VA_ARGS__)	; }
#define DEBUGUTILS_INSERTQUEUELABEL(...)           { m_Context.Get<DebugUtilsObject>()->InsertQueueLabel (__VA_ARGS__)	; }
#define DEBUGUTILS_SETOBJECTNAME(...)              { m_Context.Get<DebugUtilsObject>()->SetObjectName    (__VA_ARGS__)	; }
#define DEBUGUTILS_SETOBJECTTAG(...)               { m_Context.Get<DebugUtilsObject>()->SetObjectTag     (__VA_ARGS__)	; }

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
}