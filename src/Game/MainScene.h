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
    VertexArray* obj1_vao = nullptr;
    VertexArray* obj2_vao = nullptr;
    IndexBuffer* ibo = nullptr;

    Texture* tex1 = nullptr;
    Texture* tex2 = nullptr;
    Shader* shader = nullptr;

    glm::mat4 projection;
    glm::mat4 view;

    glm::vec3 translation1;
    glm::vec3 translation2;
};
