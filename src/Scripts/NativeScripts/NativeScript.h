#pragma once
#include "Core/Core.h"
#include "Scripts/ScriptInterface.h"

namespace PlayGround {

    class NativeScript : public ScriptInterface
    {
    public:

        NativeScript() = default;
        NativeScript(const std::filesystem::path& path) : ScriptInterface(path) {};
        ~NativeScript() override = default;
    };
}