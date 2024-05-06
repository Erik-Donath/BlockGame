//
// Created by erikd on 01.05.2024.
//

#include "../Rendering/GL.h"
#include "../App/Input.h"
#include "../App/Gui.h"
#include "../Common/Debug.h"
#include "Scene.h"

void Scene::Scene::Setup() {
    Engine::Common::Debug::Setup();
}

void Scene::Scene::Finalize() {
    Engine::Common::Debug::Finalize();
}

void Scene::Scene::Update(double deltaTime) {
    Engine::Common::Debug::Update(deltaTime);
}

void Scene::Scene::Render(GLFWwindow *window) {
    Engine::Common::Debug::Render(window);
    //ImGui::ShowDemoWindow();
}
