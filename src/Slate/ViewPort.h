#pragma once
#include "Core/Core.h"
#include "Slate.h"
#include "Core/Event/SlateEvent.h"
#include "Core/Event/WindowEvent.h"
#include "Core/Event/EngineEvent.h"

namespace PlayGround::Slate {

	class ViewPort : public Slate
	{
	public:

		ViewPort(const std::string& slateName)
			: Slate(slateName)
		{}

		~ViewPort() override = default;

		void OnTick() override;

		void OnEvent(Event& event) override;

	private:

		void ResizeQuery();

		bool OnSlateResize(SlateResizeEvent& event) const {}

		bool OnWindowResizOver(WindowResizeOverEvent& event) const {}

	private:

		ImTextureID m_TextureID{};
	};

}