//
// Created by erikd on 30.04.2024.
//

#pragma once
#include <memory>

#include "Window.h"
#include "../Scene/Scene.h"

namespace Engine::App {
    class Application {
    public:
        Application();
        ~Application();

        void SetScene(const std::shared_ptr<Scene::Scene>& scene);
        void Run();

        inline void Run(const std::shared_ptr<Scene::Scene>& scene) {
            SetScene(scene);
            Run();
        }

        [[nodiscard]] inline std::shared_ptr<Scene::Scene> GetScene() const {
            return m_scene;
        }
        [[nodiscard]] inline Engine::App::Window* GetWindow() const {
            return m_window;
        }
        [[nodiscard]] inline GLFWwindow* GetWindowHandle() const {
            return m_window->GetHandle();
        }
        [[nodiscard]] inline double GetDeltaTime() const {
            return m_deltaTime;
        }

        [[nodiscard]] static double GetTime();
        [[nodiscard]] static inline Application* GetInstance() {
            return s_instance;
        }
    private:
        Engine::App::Window* m_window = nullptr;

        bool m_changedScene = false;
        std::shared_ptr<Scene::Scene> m_scene = nullptr;

        double m_deltaTime = 0.00000001;
        static Application* s_instance;
    };
}
