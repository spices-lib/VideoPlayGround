#include "RenderFrontend.h"
#include "Render/Backend/Vulkan/RenderBackend.h"

namespace PlayGround {

    SP<RenderFrontend> RenderFrontend::Create()
    {
        return CreateSP<Vulkan::RenderBackend>();
    }

}