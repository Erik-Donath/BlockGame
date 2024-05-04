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

        void Run(Scene::Scene* scene);

        [[nodiscard]] inline GLFWwindow* GetWindowHandle() const {
            return m_window->GetHandle();
        }
        [[nodiscard]] inline double GetDeltaTime() const {
            return m_deltaTime;
        }
        [[nodiscard]] static inline double GetTime() {
            return glfwGetTime();
        }
        [[nodiscard]] inline static Application* GetInstance() {
            return s_instance;
        }
    private:
        Window* m_window;
        Scene::Scene* m_scene;
        double m_deltaTime;

        static Application* s_instance;
    };
}
