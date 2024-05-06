#include <iostream>
#include "Defines.h"

#include "Engine/App/Application.h"
#include "Game/MainScene.h"

int main() {
    Engine::App::Application app;

    std::shared_ptr<Engine::Scene::Scene> mainScene = std::make_shared<MainScene>();
    app.Run(mainScene);

    return 0;
}
