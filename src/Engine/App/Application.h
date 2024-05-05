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

        void Run();
        void SetScene(std::shared_ptr<Scene::Scene>& scene);

        inline void Run(std::shared_ptr<Scene::Scene>& scene) {
            SetScene(scene);
            Run();
        }

        static double GetTime();

        [[nodiscard]] inline Window* GetWindow() const {
            return m_window;
        }
        [[nodiscard]] inline double GetDeltaTime() const {
            return m_deltaTime;
        }
        [[nodiscard]] inline std::shared_ptr<Scene::Scene> GetScene() const {
            return m_scene;
        }

        [[nodiscard]] inline static Application* GetInstance() {
            return s_instance;
        }

    private:
        bool m_changedScene = false;
        std::shared_ptr<Scene::Scene> m_scene = nullptr;

        Window* m_window = nullptr;
        double m_deltaTime = 0.0001;

        static Application* s_instance;
    };
}
