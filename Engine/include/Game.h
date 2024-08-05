//
// Created by erikd on 05.08.2024.
//

#pragma once

#include "Define.h"
#include <Application/Window.h>

struct GameInfo {
public:
    str ApplicationName;
    str ApplicationVersion;
    Engine::Application::WindowProperties WindowProperties;
};

// Static Functions that the Game has to implement
GameInfo GetGameInfo() noexcept;
void GameLoop() noexcept;
