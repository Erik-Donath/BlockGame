//
// Created by erikd on 30.04.2024.
//

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../GL/Renderer.h"
#include "Gui.h"
#include "Application.h"

using namespace Engine::App;

Application* Application::s_instance = nullptr;

Application::Application() {
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

void Application::Application::SetScene(std::shared_ptr<Scene::Scene> &scene) {
    if(m_scene) m_scene->Finalize();
    m_scene = scene;
    m_changedScene = true;
}

void Application::Application::Run() {
    if(s_instance != this) {
        std::cerr << "Error: Tried to Run Application while another Application runs." << std::endl;
        return;
    }

    if(!m_scene) {
        m_changedScene = false;
        std::cerr << "Error: Scene not set!" << std::endl;
        return;
    }

    // Create Window and Setup Gui
    m_window = new Window("Block Game", glm::ivec2(1920, 1080), WindowOptions::Default());
    Gui::Setup(m_window->GetHandle());

    // Set Render Options
    GL::Renderer::ClearColor(DefaultClearColor);
    GL::Renderer::SetBlendFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_FUNC_ADD);
    GL::Renderer::EnableBlending();
    GL::Renderer::SetMode(GL::RenderMode::Fill);

    double lastTime = GetTime();
    while(!m_window->ShouldClose()) {
        // Scene Update
        if(m_changedScene) {
            m_scene->Setup();
            m_changedScene = false;
        }

        // Begin Frame
        GL::Renderer::Clear();
        Gui::BeginFrame();

        // Calculate DeltaTime
        double now = GetTime();
        m_deltaTime = now - lastTime;
        lastTime = now;

        // Update and Render Scene
        m_scene->Update(m_deltaTime);
        m_scene->Render(*m_window);

        // End Frame
        Gui::EndFrame();
        m_window->SwapBuffers();
        Window::PollEvents();
    }

    m_scene->Finalize();
    Gui::Shutdown();
}

double Application::GetTime() {
    return glfwGetTime();
}
