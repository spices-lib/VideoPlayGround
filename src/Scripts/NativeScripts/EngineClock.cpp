#include "EngineClock.h"
#include "World/Scene/Scene.h"
#include "World/Component/ClockComponent.h"
#include "Render/Frontend/Utils.h"

namespace PlayGround {

	EngineClock::EngineClock(Scene* scene)
		: m_Scene(scene)
	{}

	void EngineClock::OnAttached()
	{
		auto& comp = m_Scene->AddComponent<ClockComponent>(m_Scene->GetRoot());
		m_Clock = &comp.GetClock();
	}

	void EngineClock::OnTick()
	{
		m_Clock->m_FrameIndex = (m_Clock->m_FrameIndex + 1) % MaxFrameInFlight;
	}
}