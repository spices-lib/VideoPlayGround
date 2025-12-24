#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Context.h"
#include "Render/Backend/Vulkan/Utils.h"
#include "ContextAccessor.h"

namespace PlayGround::Vulkan {

    class Infrastructure : public ContextAccessor, public NonCopyable
    {
    public:

        explicit Infrastructure(Context& context, EInfrastructure e);

        ~Infrastructure() override = default;

        const EInfrastructure& GetInfrastructure() const { return m_EInfrastructure; }

    protected:

        template<typename T>
        static void Destroy(T*);

    private:

        EInfrastructure m_EInfrastructure;

    };

}