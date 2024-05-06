//
// Created by erikd on 01.05.2024.
//

#pragma once
#include "../App/Window.h"

namespace Engine::Scene {
    class Scene {
        public:
        virtual void Setup();
        virtual void Finalize();

        virtual void Update(double deltaTime);
        virtual void Render(GLFWwindow* window);
    };
}

