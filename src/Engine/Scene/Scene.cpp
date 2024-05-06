//
// Created by erikd on 01.05.2024.
//

#include "../GL/GL.h"
#include "../App/Input.h"
#include "../App/Gui.h"
#include "../Common/Debug.h"
#include "Scene.h"

using namespace Engine::Scene;

void Scene::Setup() {
    Engine::Common::Debug::Setup();
}

void Scene::Finalize() {
    Engine::Common::Debug::Finalize();
}

void Scene::Update(double deltaTime) {
    Engine::Common::Debug::Update(deltaTime);
}

void Scene::Render(GLFWwindow *window) {
    Engine::Common::Debug::Render(window);
    //ImGui::ShowDemoWindow();
}
