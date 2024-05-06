//
// Created by erikd on 04.05.2024.
//
#pragma once
#include "../Engine/GL/Renderer.h"
#include "../Engine/Scene/Transform.h"

class Block {
public:
    Block();
    ~Block();

    void Update(const double deltaTime);
    void Render(const glm::mat4& vp);
private:
    Engine::GL::VertexArray* m_vao;
    Engine::GL::VertexBuffer* m_vbo;
    Engine::GL::IndexBuffer* m_ebo;

    Engine::GL::Shader* m_shader;

    Engine::Scene::ObjectTransform m_transform;

    constexpr static const float s_vertices[] = {
            -1, -1,  1, //0
            1, -1,  1, //1
            -1,  1,  1, //2
            1,  1,  1, //3
            -1, -1, -1, //4
            1, -1, -1, //5
            -1,  1, -1, //6
            1,  1, -1  //7
    };

    constexpr static const u32 s_indices[] = {
            //Top
            2, 6, 7,
            2, 3, 7,

            //Bottom
            0, 4, 5,
            0, 1, 5,

            //Left
            0, 2, 6,
            0, 4, 6,

            //Right
            1, 3, 7,
            1, 5, 7,

            //Front
            0, 2, 3,
            0, 1, 3,

            //Back
            4, 6, 7,
            4, 5, 7
    };
};
