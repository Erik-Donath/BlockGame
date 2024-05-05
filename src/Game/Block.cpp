//
// Created by erikd on 04.05.2024.
//

#include "../Engine/App/Application.h"
#include "Block.h"

Block::Block(): m_vao(nullptr), m_vbo(nullptr), m_ebo(nullptr), m_shader(nullptr) {
    m_transform.SetScale(glm::vec3(0.25f, 0.25f, 0.25f));

    m_vao = new GL::VertexArray();

    m_vbo = new GL::VertexBuffer((void*)s_vertices, sizeof(s_vertices));
    m_ebo = new GL::IndexBuffer(GL_UNSIGNED_INT, (void*)s_indices, sizeof (s_indices));

    std::vector<GL::VertexBufferElement> layout;
    layout.emplace_back(GL_FLOAT, 3); // Position
    m_vbo->SetLayout(layout);

    m_vao->AddBuffer(*m_vbo);
    m_vao->AddBuffer(*m_ebo);

    m_shader = new GL::Shader(RESOURCES_PATH "/shaders/block-vertex.glsl", RESOURCES_PATH "/shaders/block-fragment.glsl");
}

Block::~Block() {
    delete m_vao;
    delete m_vbo;
    delete m_ebo;
    delete m_shader;
}

void Block::Update(const double deltaTime) {
    double time = App::Application::GetTime();

    //m_transform.SetRotationEuler(glm::vec3(time + 0, time + 1, time + 2));

    double scale = 0.25 + ((sin(time) + 1.0) / 2.0) * 0.25;
    m_transform.SetScale(glm::vec3(scale, scale, scale));
}


void Block::Render(const glm::mat4& vp) {
    m_shader->SetMat4("u_mvp", vp * m_transform.GetModelMatrix());
    GL::Renderer::Draw(*m_vao, *m_ebo, *m_shader);
}
