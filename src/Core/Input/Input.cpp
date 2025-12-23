#include "Input.h"
#include "GLFW/InputImpl.h"

namespace PlayGround {

    std::unique_ptr<Input> Input::s_Instance = std::make_unique<GLFW::InputImpl>();

}