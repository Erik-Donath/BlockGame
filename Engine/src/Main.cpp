//
// Created by erikd on 05.08.2024.
//

#include <Game.h>
using namespace Engine::Application;

i32 main() {
    GameInfo info = GetGameInfo();

    Window gameWindow(info.ApplicationName, info.WindowProperties);

    while(!gameWindow.ShouldClose()) {
        gameWindow.SwapBuffers();
        GameLoop();
        Window::PollEvents();
    }
    gameWindow.close();
    return 0;
}