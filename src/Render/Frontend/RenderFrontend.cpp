#include "RenderFrontend.h"
#include "Render/Backend/Vulkan/RenderBackend.h"
#include "Window/Window.h"

namespace PlayGround {

    SP<RenderFrontend> RenderFrontend::Create()
    {
        return CreateSP<Vulkan::RenderBackend>(&Window::Instance());
    }

}