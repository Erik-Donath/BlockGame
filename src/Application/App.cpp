//
// Created by erikd on 27.04.2024.
//

#include <glm/glm.hpp>

#include "ImGUI.h"
#include "App.h"

void App::Run(Scene& scene) {
    m_window = new Window("Block Game", glm::ivec2(1920, 1080), WindowProperties());
    m_renderer = new Renderer();
    m_scene = &scene;

    ImGUISetup(m_window->GetHandle());
    m_renderer->SetBlendType(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_FUNC_ADD);
    m_renderer->ClearColor();
    m_scene->Init(*m_window);

    while (!m_window->ShouldClose()) {
        m_renderer->Clear();
        ImGUIBeforeRender();

        m_scene->Update();
        m_scene->Render(*m_renderer);

        ImGUIAfterRender();
        m_window->SwapBuffers();
        Window::PollEvents();
    }

    m_scene->Shutdown();
    ImGuiShutdown();

    delete m_renderer;
    delete m_window;

    m_scene = nullptr;
}

App::~App() {
    delete m_renderer;
    delete m_window;
}
// 1.164