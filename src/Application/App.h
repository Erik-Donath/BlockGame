//
// Created by erikd on 27.04.2024.
//
#pragma once
#include <glm/glm.hpp>
#include "../Rendering/gfx/GL.h"
#include "../Rendering/base/Window.h"
#include "../Rendering/base/Renderer.h"

#include "Scene.h"

class App {
public:
    ~App();

    void Run(Scene& scene);
private:
    Window* m_window = nullptr;
    Renderer* m_renderer = nullptr;
    Scene* m_scene = nullptr;
};
