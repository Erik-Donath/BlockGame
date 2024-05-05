//
// Created by erikd on 01.05.2024.
//

#include "../GL/GL.h"
#include "../App/Input.h"
#include "../Common/Debug.h"
//#include "../App/Gui.h"

#include "Scene.h"

using namespace Engine::Scene;

void Scene::Setup() {
    Common::Debug::Setup();
}

void Scene::Finalize() {
    Common::Debug::Finalize();
}

void Scene::Update(double deltaTime) {
    Common::Debug::Update(deltaTime);
}

void Scene::Render(App::Window &window) {
    Common::Debug::Render(window.GetHandle());
    //ImGui::ShowDemoWindow();
}
