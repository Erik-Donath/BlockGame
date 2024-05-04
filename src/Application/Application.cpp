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

void Application::Application::Run(Scene::Scene* scene) {
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

    double lastTime = glfwGetTime();

    m_scene->Setup();
    while(!m_window->ShouldClose()) {
        // Begin Frame
        Rendering::Renderer::Clear();
        ImGUIBeforeRender();

        // Calculate DeltaTime
        double now = glfwGetTime();
        m_deltaTime = now - lastTime;
        lastTime = now;

        // Update and Render Scene
        m_scene->Update(m_deltaTime);
        m_scene->Render(m_window->GetHandle());

        // Finalize Frame
        ImGUIAfterRender();
        m_window->SwapBuffers();
        Window::PollEvents();
    }
    m_scene->Finalize();
    ImGuiShutdown();
}
// 935
// => 229