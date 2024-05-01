//
// Created by erikd on 01.05.2024.
//

#include "../Rendering/GL.h"
#include "../Application/Input.h"
#include "../Application/ImGUI.h"
#include "Scene.h"

void Scene::Update(double deltaTime) {
    // Nothing here
}

void Scene::Render(GLFWwindow *window) {
    ImGui::ShowDemoWindow();

    if(Application::Input::IsPressed(Key(E))) {
        ImGui::Begin("Hello");
        ImGui::Text("Debug Text");
        ImGui::End();
    }
    if(Application::Input::IsReleased(Key(E))) {
        ImGui::Begin("Not Hello");
        ImGui::Text("Not Debug Text");
        ImGui::End();
    }
}
