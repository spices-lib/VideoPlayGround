#pragma once
#include "Core/Core.h"
#include "Core/Event/Event.h"

#include <filesystem>

namespace PlayGround {

    class ScriptInterface : public NonCopyable
    {
    public:

        ScriptInterface() = default;
        ScriptInterface(const std::filesystem::path& path) : m_ScriptPath(path) {};
        ~ScriptInterface() override = default;

        virtual void OnConstruct() {}
        virtual void OnAttached() {}
        virtual void OnTick() {}
        virtual void OnDestroy() {}
        virtual void OnDetached() {}
        virtual void OnEvent(Event& e) {}

        std::string GetFileString() const { return m_ScriptPath.generic_string(); }

    protected:

        std::filesystem::path m_ScriptPath;
    };
}