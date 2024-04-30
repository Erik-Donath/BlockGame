//
// Created by erikd on 30.04.2024.
//

#include "ImGUI.h"
#include "Application.h"
#include "../Rendering/Renderer.h"

void Application::Application::Run() {
    m_window = std::make_unique<Window>("Block Game", glm::ivec2(1920, 1080), WindowProperties());

    ImGUISetup(m_window->GetHandle());

    Rendering::Renderer::ClearColor(DefaultClearColor);
    Rendering::Renderer::SetBlendFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_FUNC_ADD);
    Rendering::Renderer::EnableBlending();

    bool vsnc = true;
    m_window->SetVSNC(vsnc);

    while(!m_window->ShouldClose()) {
        Rendering::Renderer::Clear();
        ImGUIBeforeRender();

        //m_scene->Update();
        //m_scene->Render(*m_renderer);

        ImGuiIO& io = ImGui::GetIO();
        ImGui::Begin("Application Info");

        GLCall(ImGui::Text("OpenGL Version: %s", glGetString(GL_VERSION)));
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        
        ImGui::Text("Options");
        if(ImGui::Checkbox("VSNC", &vsnc)) {
            m_window->SetVSNC(vsnc);
        }

        ImGui::End();

        ImGUIAfterRender();
        m_window->SwapBuffers();
        Window::PollEvents();
    }
    ImGuiShutdown();
}
