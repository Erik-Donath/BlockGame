//
// Created by erikd on 27.04.2024.
//

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "../Rendering/Base.h"
#include "MainScene.h"

void MainScene::Init(const Window& window) {
    float obj1_vertices[] = {
            400.0f,  400.0f, 1.0f, 1.0f,   // top right
            400.0f, 100.0f, 1.0f, 0.0f,  // bottom right
            100.0f, 100.0f, 0.0f, 0.0f, // bottom left
            100.0f, 400.0f, 0.0f, 1.0f // top left
    };
    float obj2_vertices[] = {
            400.0f,  400.0f, 1.0f, 1.0f,   // top right
            400.0f, 100.0f, 1.0f, 0.0f,  // bottom right
            100.0f, 100.0f, 0.0f, 0.0f, // bottom left
            100.0f, 400.0f, 0.0f, 1.0f // top left
    };
    uint32_t indices[] = {     // note that we start from 0
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };

    obj1_vao = new VertexArray();
    obj2_vao = new VertexArray();

    VertexBuffer obj1_vbo(obj1_vertices, sizeof(obj1_vertices));
    VertexBuffer obj2_vbo(obj2_vertices, sizeof(obj2_vertices));

    VertexBufferLayout layout;
    layout.Push<GL_FLOAT>(2); // Position
    layout.Push<GL_FLOAT>(2); // UV-Coord

    obj1_vao->AddBuffer(obj1_vbo, layout);
    obj2_vao->AddBuffer(obj2_vbo, layout);

    ibo = new IndexBuffer(GL_UNSIGNED_INT, indices, sizeof(indices));

    tex1 = new Texture(RESOURCES_PATH "/logo.jpg");
    tex2 = new Texture(RESOURCES_PATH "/hello.png");
    shader = new Shader(RESOURCES_PATH "/shader.glsl");

    // Projection Matrix
    glm::ivec2 wSize = window.GetSize();
    projection = glm::ortho(0.0f, (float)wSize.x, 0.0f, (float)wSize.y, -1.0f, 1.0f);
    view = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, 0.0f));
    translation1 = glm::vec3(200.0f, 200.0f, 0.0f);
    translation2 = glm::vec3(200.0f, 200.0f, 0.0f);
}

void MainScene::Shutdown() {
    delete obj1_vao; obj1_vao = nullptr;
    delete obj2_vao; obj2_vao = nullptr;
    delete ibo; ibo = nullptr;

    delete tex1; tex1 = nullptr;
    delete tex2; tex2 = nullptr;
    delete shader; shader = nullptr;
}

void MainScene::Update() { }

void MainScene::Render(const Renderer &renderer) {
    // Binding Texture
    tex1->Bind(0);
    tex2->Bind(1);

    glm::mat4 vp = projection * view;

    shader->SetMat4("uMVP", vp * glm::translate(glm::mat4(1.0f), translation1));
    shader->SetSampler("u_Texture", 0);
    renderer.Draw(*obj1_vao, *ibo, *shader);

    shader->SetMat4("uMVP", vp * glm::translate(glm::mat4(1.0f), translation2));
    shader->SetSampler("u_Texture", 1);
    renderer.Draw(*obj2_vao, *ibo, *shader);

    ImGuiIO& io = ImGui::GetIO();
    ImGui::Begin("Application Info");
    GLCall(ImGui::Text("OpenGL Version: %s", glGetString(GL_VERSION)));
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();

    ImGui::Begin("Inspector");

    ImGui::PushID("Obj1");
    ImGui::Text("Object 1");
    ImGui::SliderFloat3("Translation", &translation1.x, 0.0f, 2000.0f);
    ImGui::PopID();

    ImGui::PushID("Obj2");
    ImGui::Text("Object 2");
    ImGui::SliderFloat3("Translation", &translation2.x, 0.0f, 2000.0f);
    ImGui::PopID();

    ImGui::End();
}
