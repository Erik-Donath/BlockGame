//
// Created by erikd on 04.05.2024.
//

#pragma once
#include "../Rendering/Renderer.h"

namespace Engine::Common {
    class Debug {
    public:
        static void Setup();
        static void Finalize();
        static void Update(double deltaTime);
        static void Render(GLFWwindow* window);
    private:
        static bool s_vsync;
        static Rendering::RenderMode s_renderMode;
    };
}