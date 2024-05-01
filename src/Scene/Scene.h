//
// Created by erikd on 01.05.2024.
//

#pragma once
#include "../Application/Window.h"

class Scene {
public:
    virtual void Update(double deltaTime);
    virtual void Render(GLFWwindow* window);
};

