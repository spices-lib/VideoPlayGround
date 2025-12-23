#pragma once
#include "Core/Core.h"
#include "Core/Application.h"

int main() {

    auto& engine = PlayGround::Application::Instance();
    engine.Run();
    PlayGround::Application::Destroy();

    return 0;
}
