//
// Created by erikd on 30.04.2024.
//

#include <iostream>

#include "../Rendering/Renderer.h"
#include "ImGUI.h"
#include "Application.h"

Application::Application* Application::Application::s_instance = nullptr;

Application::Application::Application(): m_window(nullptr), m_scene(nullptr), m_deltaTime(0.0001) {
    if(s_instance) {
        std::cerr << "Error: Application should be a singleton!" << std::endl;
        return;
    }
    s_instance = this;
}

Application::Application::~Application() {
    if(s_instance == this) {
        s_instance = nullptr;
    }
    delete m_window;
}

void Application::Application::Run(Scene* scene) {
    if(s_instance != this) {
        std::cerr << "Error: Tried to Run Application while another Application runs." << std::endl;
        return;
    }

    m_scene = scene;
    m_window = new Window("Block Game", glm::ivec2(1920, 1080), WindowProperties());

    ImGUISetup(m_window->GetHandle());

    Rendering::Renderer::ClearColor(DefaultClearColor);
    Rendering::Renderer::SetBlendFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_FUNC_ADD);
    Rendering::Renderer::EnableBlending();

    bool vsync = true;
    Window::SetVSYNC(vsync);

    double lastTime = glfwGetTime();
    while(!m_window->ShouldClose()) {
        Rendering::Renderer::Clear();
        ImGUIBeforeRender();

        // Calculate DeltaTime
        double now = glfwGetTime();
        m_deltaTime = now - lastTime;
        lastTime = now;

        m_scene->Update(m_deltaTime);
        m_scene->Render(m_window->GetHandle());

        ImGuiIO& io = ImGui::GetIO();
        ImGui::Begin("Application Info");

        GLCall(ImGui::Text("OpenGL Version: %s", glGetString(GL_VERSION)));
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::Text("Application delta Time %f ms/frame", m_deltaTime);

        ImGui::Text("Options");
        if(ImGui::Checkbox("VSYNC", &vsync)) {
            Window::SetVSYNC(vsync);
        }

        ImGui::End();

        ImGUIAfterRender();
        m_window->SwapBuffers();
        Window::PollEvents();
    }
    ImGuiShutdown();
}
// 935
// => 229