//
// Created by erikd on 30.04.2024.
//

#pragma once
#include "Window.h"
#include "../Scene/Scene.h"

namespace Application {
    class Application {
    public:
        Application();
        ~Application();

        void Run(Scene* scene);

        [[nodiscard]] inline GLFWwindow* GetWindowHandle() const {
            return m_window->GetHandle();
        }
        [[nodiscard]] inline double GetDeltaTime() {
            return m_deltaTime;
        }
        [[nodiscard]] inline static Application* GetInstance() {
            return s_instance;
        }
    private:
        Window* m_window;
        Scene* m_scene;
        double m_deltaTime;

        static Application* s_instance;
    };
}
