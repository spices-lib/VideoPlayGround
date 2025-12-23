#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Context.h"
#include "Render/Backend/Vulkan/Utils.h"

namespace PlayGround::Vulkan {

    class Infrastructure : public NonCopyable
    {
    public:

        explicit Infrastructure(Context& context);

        ~Infrastructure() override;

    protected:

        template<typename T>
        static void Destroy(T*);

    protected:

        Context& m_Context;

    };

    template <typename T>
    void Infrastructure::Destroy(T*)
    {
        CORE_WARN("Vulkan Infrastructure Not implement Destroy API.")
    }

}