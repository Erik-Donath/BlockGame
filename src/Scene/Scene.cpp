//
// Created by erikd on 01.05.2024.
//

#include "../Application/ImGUI.h"
#include "Scene.h"

void Scene::Update(double deltaTime) {
    // Nothing here
}

void Scene::Render(GLFWwindow *window) {
    ImGui::ShowDemoWindow();
}
