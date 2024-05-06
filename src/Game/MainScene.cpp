//
// Created by erikd on 04.05.2024.
//

#include "MainScene.h"

MainScene::MainScene(): m_block(nullptr), m_camera(nullptr) { }

MainScene::~MainScene() {
    delete m_block;
    delete m_camera;
}

void MainScene::Setup() {
    Scene::Setup();
    m_block  = new Block();
    m_camera = new ::Scene::Camera();
}

void MainScene::Finalize() {
    Scene::Finalize();
    delete m_block;
    delete m_camera;
    m_block = nullptr;
    m_camera = nullptr;
}

void MainScene::Update(double deltaTime) {
    m_block->Update(deltaTime);
    m_camera->Update(deltaTime);
    Scene::Update(deltaTime);
}

void MainScene::Render(GLFWwindow *window) {
    const glm::mat4& vp = m_camera->GetVPMatrix();

    m_block->Render(vp);
    Scene::Render(window);
}


