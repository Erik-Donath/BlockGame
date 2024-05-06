//
// Created by erikd on 30.04.2024.
//

#include <iostream>

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

Application::~Application() {
    if(s_instance == this) s_instance = nullptr;
    delete m_window;
}

void Application::SetScene(const std::shared_ptr<Scene::Scene> &scene) {
    if(m_scene) m_scene->Finalize(); // FIXME: Can curse bug when called twice before Run().

    m_scene = scene;
    m_changedScene = true; // Setup should only be called, if the Application is loaded.
}

void Application::Run() {
    if(s_instance != this) {
        std::cerr << "Error: Tried to Run Application while another Application runs." << std::endl;
        return;
    }

    if(!m_scene) {
        std::cerr << "Error: Tried to Run Application without Scene set." << std::endl;
        return;
    }

    m_window = new Window("Block Game", glm::ivec2(1920, 1080), WindowProperties::Default());

    Gui::ImGUISetup(m_window->GetHandle());

    GL::Renderer::ClearColor(DefaultClearColor);
    GL::Renderer::SetBlendFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_FUNC_ADD);
    GL::Renderer::EnableBlending();
    GL::Renderer::SetMode(GL::RenderMode::Fill);

    double lastTime = glfwGetTime();

    while(!m_window->ShouldClose()) {
        if(m_changedScene) {
            m_scene->Setup();
            m_changedScene = false;
        }

        // Begin Frame
        GL::Renderer::Clear();
        Gui::ImGUIBeforeRender();

        // Calculate DeltaTime
        double now = glfwGetTime();
        m_deltaTime = now - lastTime;
        lastTime = now;

        // Update and Render Scene
        m_scene->Update(m_deltaTime);
        m_scene->Render(m_window->GetHandle());

        // Finalize Frame
        Gui::ImGUIAfterRender();
        m_window->SwapBuffers();
        Window::PollEvents();
    }
    m_scene->Finalize();
    Gui::ImGuiShutdown();
}
// 935
// => 229
double Application::GetTime() {
    return glfwGetTime();
}
