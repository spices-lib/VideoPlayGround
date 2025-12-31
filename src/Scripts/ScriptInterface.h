#pragma once
#include "Core/Core.h"
#include "Core/Event/Event.h"
#include "Core/UUID.h"
#include <filesystem>

namespace PlayGround {

    class ScriptInterface : public NonCopyable
    {
    public:

        ScriptInterface() : m_ScriptID(UUID()) {};
        ~ScriptInterface() override = default;

        virtual void OnConstruct() {}
        virtual void OnAttached() {}
        virtual void OnTick() {}
        virtual void OnDestroy() {}
        virtual void OnDetached() {}
        virtual void OnEvent(Event& e) {}

        const UUID& GetUUID() const { return m_ScriptID; }

    protected:

        UUID m_ScriptID;
    };
}