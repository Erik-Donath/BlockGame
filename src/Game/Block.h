//
// Created by erikd on 04.05.2024.
//
#pragma once
#include "../Rendering/Renderer.h"
#include "../Scene/Transform.h"

class Block {
public:
    Block();
    ~Block();

    void Update(const double deltaTime);
    void Render(const glm::mat4& vp);
private:
    Rendering::VertexArray* m_vao;
    Rendering::VertexBuffer* m_vbo;
    Rendering::IndexBuffer* m_ebo;

    Rendering::Shader* m_shader;

    Scene::ObjectTransform m_transform;

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
