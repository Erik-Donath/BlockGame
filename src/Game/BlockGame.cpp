//
// Created by erikd on 19.10.2024.
//

#include "../GL.h"
#include "GLFW/glfw3.h"

#include "BlockGame.h"
#include "Test.h"

BlockGame::BlockGame(): Application("Block Game", {800, 600}) { }

void BlockGame::setup() {
    Window::SwapInterval(m_vsync);

    GLCall(glClearColor(0.6f, 0.8f, 1.0f, 1.0f));
    GLCall(glEnable(GL_DEPTH_TEST));

    //GLCall(glEnable(GL_CULL_FACE));
    //GLCall(glCullFace(GL_BACK));

    Test::start(*getWindow());
}

void BlockGame::update(double dt) {
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    Test::render(dt);

    // Settings
    ImGui::Begin("Settings");
    if(ImGui::Button(m_vsync ? "VSYNC OFF" : "VSYNC ON")) {
        m_vsync = !m_vsync;
        Window::SwapInterval(m_vsync);
    }
    if(ImGui::Button("Exit Game")) {
        getWindow()->Close();
    }
    ImGui::End();

    // Debug
    ImGui::Begin("Info");
    ImGui::Text("VSYNC: %s", m_vsync ? "ON" : "OFF");
    ImGui::Text("FPS: %d\n(Min: %d, Max: %d, Avg: %d)", getFPS(), getMinFPS(), getMaxFPS(), getAvgFPS());
    ImGui::Text("MS: %f", dt * 100.0);
    ImGui::End();
}

void BlockGame::shutdown() {
    Test::stop();
}
