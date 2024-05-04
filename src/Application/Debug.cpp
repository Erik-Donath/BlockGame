//
// Created by erikd on 04.05.2024.
//

#include "Window.h"
#include "ImGUI.h"
#include "../Rendering/Renderer.h"

#include "Debug.h"

bool Application::Debug::s_vsync     = false;
bool Application::Debug::s_wireframe = false;

void Application::Debug::Setup() {
    Window::SetVSYNC(s_vsync);
    Rendering::Renderer::SetWireframeMode(s_wireframe);
}

void Application::Debug::Finalize() { }

void Application::Debug::Update(double deltaTime) { }

void Application::Debug::Render(GLFWwindow *window) {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Begin("Application Info");

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    GLCall(ImGui::Text("OpenGL Version: %s", glGetString(GL_VERSION)));

    ImGui::Text("Settings");
    if(ImGui::Checkbox("Vsync", &s_vsync)) Window::SetVSYNC(s_vsync);
    if(ImGui::Checkbox("Wireframe", &s_wireframe)) Rendering::Renderer::SetWireframeMode(s_wireframe);

    ImGui::End();
}