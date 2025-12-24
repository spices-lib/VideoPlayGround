#pragma once
#include "Core/Core.h"
#include "Scripts/ScriptInterface.h"

namespace PlayGround {

    class NativeScript : public ScriptInterface
    {
    public:

        NativeScript() = default;
        ~NativeScript() override = default;
    };
}