#pragma once
#include "Core/Core.h"

namespace PlayGround {

    enum class WorldMarkBit : uint32_t
    {
        DynamicScriptTick  = 0,
        DynamicScriptEvent,

        Count
    };

}
