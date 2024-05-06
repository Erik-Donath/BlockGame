//
// Created by erikd on 01.05.2024.
//

#include "../Rendering/GL.h"
#include "../Application/Input.h"
#include "../Application/ImGUI.h"
#include "../Application/Debug.h"
#include "Scene.h"

void Scene::Scene::Setup() {
    Application::Debug::Setup();
}

void Scene::Scene::Finalize() {
    Application::Debug::Finalize();
}

void Scene::Scene::Update(double deltaTime) {
    Application::Debug::Update(deltaTime);
}

void Scene::Scene::Render(GLFWwindow *window) {
    Application::Debug::Render(window);
    //ImGui::ShowDemoWindow();
}
