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

        virtual void OnConstruct() = 0;
        virtual void OnAttached() = 0;
        virtual void OnTick() = 0;
        virtual void OnDestroy() = 0;
        virtual void OnDetached() = 0;
        virtual void OnEvent(Event& e) = 0;

        std::string GetFileString() const { return m_ScriptPath.generic_string(); }

    protected:

        std::filesystem::path m_ScriptPath;
    };
}