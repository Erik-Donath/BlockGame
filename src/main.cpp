#include <iostream>
#include "Defines.h"

#include "Application/Application.h"
#include "Game/MainScene.h"

int main() {
    Application::Application app;
    auto* mainScene = new MainScene();
    app.Run(mainScene);

    delete mainScene;
    return 0;
}
