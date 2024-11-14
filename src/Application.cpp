//
// Created by erikd on 19.10.2024.
//

#include <cmath>
#include <climits>

#include <GLFW/glfw3.h>
#include "Application.h"

Application::Application(const std::string &name, glm::ivec2 size) {
    m_window = new Window(name, size);
    m_gui    = new GUI(*m_window);
}

Application::~Application() {
    delete m_gui;
    delete m_window;
}

void Application::run() {
    setup();

    fps = 0, fps_avg = 0;
    fps_min = INT_MAX;
    fps_max = INT_MIN;

    bool first_frame = true;
    double last_frame = 0;

    while(m_window->Opened()) {
        double current_frame = glfwGetTime();
        double delta_time = 1;

        if(!first_frame) {
            delta_time = current_frame - last_frame;
            fps = static_cast<int>(round(1.0 / delta_time));
            fps_avg = static_cast<int>(round((fps_avg + fps) / 2.0));
            if(fps < fps_min) fps_min = fps;
            if(fps > fps_max) fps_max = fps;
        }
        last_frame = current_frame;

        GUI::Before();
        update(delta_time);

        GUI::After();
        m_window->SwapBuffers();
        Window::PollEvents();
        first_frame = false;
    }

    shutdown();
}

void Application::setup() {}
void Application::shutdown() {}
void Application::update(double dt) { }
