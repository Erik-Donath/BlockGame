//
// Created by erikd on 27.04.2024.
//
#pragma once
#include "../Application/GFX.h"
#include "../Application/Scene.h"

class MainScene : public Scene {
public:
    void Init(const Window& window) override;
    void Shutdown() override;

    void Update() override;
    void Render(const Renderer& renderer) override;
private:
    Rendering::VertexArray* obj1_vao = nullptr;
    Rendering::VertexArray* obj2_vao = nullptr;
    Rendering::IndexBuffer* ibo = nullptr;

    Rendering::Texture* tex1 = nullptr;
    Rendering::Texture* tex2 = nullptr;
    Rendering::Shader* shader = nullptr;

    glm::mat4 projection;
    glm::mat4 view;

    glm::vec3 translation1;
    glm::vec3 translation2;
};
