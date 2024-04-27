#include <iostream>
#include "Defines.h"

#include "Application/App.h"
#include "Game/MainScene.h"

int main() {
    App app;
    auto* start = new MainScene();

    app.Run(*start);

    delete start;
    return 0;
}
