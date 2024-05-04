//
// Created by erikd on 04.05.2024.
//

#include "MainScene.h"

MainScene::MainScene(): m_block(nullptr) { }

MainScene::~MainScene() {
    delete m_block;
}

void MainScene::Setup() {
    Scene::Setup();
    m_block = new Block();
}

void MainScene::Finalize() {
    Scene::Setup();
    delete m_block;
}

void MainScene::Update(double deltaTime) {
    m_block->Update(deltaTime);
    Scene::Update(deltaTime);
}

void MainScene::Render(GLFWwindow *window) {
    m_block->Render(glm::mat4(1));
    Scene::Render(window);
}


