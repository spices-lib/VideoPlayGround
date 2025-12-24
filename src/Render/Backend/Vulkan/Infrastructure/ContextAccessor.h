#pragma once
#include "Core/Core.h"

namespace PlayGround::Vulkan {
    class Context;
}

namespace PlayGround::Vulkan {

    class ContextAccessor
    {
    public:

        ContextAccessor(Context& context) : m_Context(context) {}

        virtual ~ContextAccessor() = default;

        constexpr Context& GetContext() { return m_Context; }
        
    private:

        Context& m_Context;
    };
}
