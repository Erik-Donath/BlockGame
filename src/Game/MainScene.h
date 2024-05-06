//
// Created by erikd on 04.05.2024.
//

#pragma once
#include "../Engine/Scene/Scene.h"
#include "../Engine/Scene/Camera.h"
#include "Block.h"

class MainScene: public Engine::Scene::Scene {
public:
    MainScene();
    ~MainScene();

    void Setup() override;
    void Finalize() override;
    void Update(double deltaTime) override;
    void Render(GLFWwindow* window) override;

private:
    Block* m_block;
    Engine::Scene::Camera* m_camera;
};

