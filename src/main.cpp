#include <iostream>
#include "Defines.h"

#include "Application/Application.h"

int main() {
    Application::Application app;
    auto* mainScene = new Scene();
    app.Run(mainScene);

    delete mainScene;
    return 0;
}
