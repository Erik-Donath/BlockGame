//
// Created by erikd on 01.05.2024.
//

#pragma once
#include "../Application/Window.h"

namespace Scene {
    class Scene {
        public:
        virtual void Setup();
        virtual void Finalize();

        virtual void Update(double deltaTime);
        virtual void Render(GLFWwindow* window);
    };
}

