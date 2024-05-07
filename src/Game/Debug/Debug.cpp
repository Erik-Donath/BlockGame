//
// Created by erikd on 04.05.2024.
//

#include "../../Engine/App/Window.h"
#include "../../Engine/App/Gui.h"
#include "../../Engine/GL/Renderer.h"

#include "Debug.h"

using namespace Engine::Common;

// Render Options
static const char* renderOptions[] = {"Point", "Line", "Fill"};
static byte GetOptionFromRenderMode(Engine::GL::RenderMode mode) {
    switch (mode) {
        case GL_POINT: return 0;
        case GL_LINE: return 1;
        case GL_FILL: return 2;
        default: return 0;
    }
}
static Engine::GL::RenderMode GetRenderModeFromOption(u8 id) {
    switch (id) {
        case 0: return Engine::GL::RenderMode::Point;
        case 1: return Engine::GL::RenderMode::Line;
        case 2: return Engine::GL::RenderMode::Fill;
        default: return Engine::GL::RenderMode::Point;
    }
}

bool Debug::s_vsync = false;

float Debug::s_renderPointSize = 1.0f;
float Debug::s_renderLineWidth = 1.0f;
Engine::GL::RenderMode Debug::s_renderMode = Engine::GL::RenderMode::Fill;

void Debug::Setup() {
    Engine::App::Window::SetVSYNC(s_vsync);
    GL::Renderer::SetMode(s_renderMode);
}

void Debug::Finalize() { }

void Debug::Update(double deltaTime) { }

void Debug::Render(GLFWwindow *window) {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Begin("Application Info");

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    GLCall(ImGui::Text("OpenGL Version: %s", glGetString(GL_VERSION)));

    ImGui::Text("Settings");
    if(ImGui::Checkbox("Vsync", &s_vsync)) Engine::App::Window::SetVSYNC(s_vsync);

    // Render Options
    cstr currentRenderOption = renderOptions[GetOptionFromRenderMode(s_renderMode)];
    if(ImGui::BeginCombo("Render Mode", currentRenderOption)) {
        for(u8 i = 0; i < 3; i++) {
            cstr option = renderOptions[i];
            bool selected = (currentRenderOption == option);

            if(ImGui::Selectable(option, selected)) {
                s_renderMode = GetRenderModeFromOption(i);
                GL::Renderer::SetMode(s_renderMode, s_renderLineWidth, s_renderPointSize);
            }

            if(selected) ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    if(s_renderMode == Engine::GL::RenderMode::Point && ImGui::SliderFloat("Render Point Size", &s_renderPointSize, 1.0f, 10.0f))
        GL::Renderer::SetMode(s_renderMode, s_renderLineWidth, s_renderPointSize);
    if(s_renderMode == Engine::GL::RenderMode::Line && ImGui::SliderFloat("Render Line Width", &s_renderLineWidth, 1.0f, 10.0f))
        GL::Renderer::SetMode(s_renderMode, s_renderLineWidth, s_renderPointSize);


    ImGui::End();
}