//
// Created by erikd on 04.05.2024.
//

#pragma once
#include "../Scene/Scene.h"
#include "Block.h"

class MainScene: public Scene::Scene {
public:
    MainScene();
    ~MainScene();

    void Setup() override;
    void Finalize() override;
    void Update(double deltaTime) override;
    void Render(GLFWwindow* window) override;

private:
    Block* m_block;
};

