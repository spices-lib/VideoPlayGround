#include "ViewPort.h"
#include <glm.hpp>

namespace PlayGround::Slate {

	void ViewPort::OnTick()
	{
		ResizeQuery();

		ImGui::SetNextWindowBgAlpha(0.5f);

		bool open;
		ImGui::Begin(m_SlateName.c_str(), &open, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);

		ImGui::Image(m_TextureID, m_SlateSize);

		ImGui::End();
	}

	void ViewPort::OnEvent(Event& event)
	{
		
	}

	void ViewPort::ResizeQuery()
	{
		ImVec2 tempSize = ImVec2(glm::max(ImGui::GetContentRegionAvail().x, 1.0f), glm::max(ImGui::GetContentRegionAvail().y, 1.0f));

		if (m_SlateSize.x != tempSize.x || m_SlateSize.y != tempSize.y)
		{
			{
				EngineEvent event(EngineEventBit::StopTheGame);

				Event::GetEventCallbackFn()(event);
			}

			{
				SlateResizeEvent event(static_cast<uint32_t>(tempSize.x), static_cast<uint32_t>(tempSize.y));

				Event::GetEventCallbackFn()(event);
			}
		}

		m_SlateSize = tempSize;
	}

}