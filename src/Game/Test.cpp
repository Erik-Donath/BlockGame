//
// Created by erikd on 10.11.2024.
//

#include "../GL.h"
#include "../Buffer.h"
#include "../VertexArray.h"
#include "../Shader.h"

#include "Camera.h"
#include "Test.h"

VertexArray* vao;
ShaderProgram* shader;
Camera* camera;

constexpr float vertices[] = {
        // Position                     // Farbe
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // 0
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  // 1
        0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  // 2
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  // 3
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  // 4
        0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // 5
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  // 6
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f   // 7
};
constexpr unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,  // Rückseite
        4, 5, 6, 6, 7, 4,  // Vorderseite
        0, 4, 7, 7, 3, 0,  // Linke Seite
        1, 5, 6, 6, 2, 1,  // Rechte Seite
        3, 2, 6, 6, 7, 3,  // Oben
        0, 1, 5, 5, 4, 0   // Unten
};

void Test::start(Window& window) {
    vao = new VertexArray();
    vao->SetIndexBuffer(std::make_shared<IndexBuffer>(&indices, sizeof(indices)));
    vao->AddBuffer(std::make_shared<ArrayBuffer>(&vertices, sizeof(vertices)), {
        VertexAttribute(GL_FLOAT, 3),
        VertexAttribute(GL_FLOAT, 3)
    });

    shader = new ShaderProgram({
        std::make_shared<Shader>("res/vertex.glsl", ShaderType::VertexShader),
        std::make_shared<Shader>("res/fragment.glsl", ShaderType::FragmentShader)
    });

    camera = new Camera(window, glm::vec3(0,0,0), 90);
}

void Test::render(double deltaTime) {
    camera->update((float)deltaTime);
    shader->use();

    shader->setUniformMat4("model", glm::mat4(1.0f));
    shader->setUniformMat4("view", camera->GetViewMatrix());
    shader->setUniformMat4("projection", camera->GetProjectionMatrix());

    vao->Bind();
    GLCall(glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, nullptr));
}

void Test::stop() {
    delete vao;
    delete shader;
    delete camera;
}
