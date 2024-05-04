//
// Created by erikd on 04.05.2024.
//

#include "Window.h"
#include "ImGUI.h"
#include "../Rendering/Renderer.h"

#include "Debug.h"

// Render Options
static const char* renderOptions[] = {"Point", "Line", "Fill"};
static byte GetOptionFromRenderMode(Rendering::RenderMode mode) {
    switch (mode) {
        case GL_POINT: return 0;
        case GL_LINE: return 1;
        case GL_FILL: return 2;
        default: return 0;
    }
}
static Rendering::RenderMode GetRenderModeFromOption(u8 id) {
    switch (id) {
        case 0: return Rendering::RenderMode::Point;
        case 1: return Rendering::RenderMode::Line;
        case 2: return Rendering::RenderMode::Fill;
        default: return Rendering::RenderMode::Point;
    }
}

bool Application::Debug::s_vsync = false;
Rendering::RenderMode Application::Debug::s_renderMode = Rendering::RenderMode::Line;

void Application::Debug::Setup() {
    Window::SetVSYNC(s_vsync);
    Rendering::Renderer::SetMode(s_renderMode);
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

    // Render Options
    cstr currentRenderOption = renderOptions[GetOptionFromRenderMode(s_renderMode)];
    if(ImGui::BeginCombo("Render Mode", currentRenderOption)) {
        for(u8 i = 0; i < 3; i++) {
            cstr option = renderOptions[i];
            bool selected = (currentRenderOption == option);

            if(ImGui::Selectable(option, selected)) {
                s_renderMode = GetRenderModeFromOption(i);
                Rendering::Renderer::SetMode(s_renderMode);
            }

            if(selected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
    ImGui::End();
}