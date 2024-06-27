//
// Created by erikd on 04.05.2024.
//

#pragma once
#include "../../Engine/GL/Renderer.h"

namespace Engine::Common {
    class Debug {
    public:
        static void Setup();
        static void Finalize();
        static void Update(double deltaTime);
        static void Render(GLFWwindow* window);
    private:
        static bool s_vsync;

        static bool s_active;
        static bool s_lastPressed;

        static float s_renderPointSize;
        static float s_renderLineWidth;
        static GL::RenderMode s_renderMode;
    };
}
