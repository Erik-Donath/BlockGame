#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "base/GFX.h"
#include "base/Renderer.h"

#include <imgui.h>
#include "base/ImGui.h"

float obj1_vertices[] = {
         400.0f,  400.0f, 1.0f, 1.0f,   // top right
         400.0f, 100.0f, 1.0f, 0.0f,  // bottom right
        100.0f, 100.0f, 0.0f, 0.0f, // bottom left
        100.0f, 400.0f, 0.0f, 1.0f // top left
};
GLuint obj1_indices[] = {     // note that we start from 0
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
};
float obj2_vertices[] = {
        400.0f,  400.0f, 1.0f, 1.0f,   // top right
        400.0f, 100.0f, 1.0f, 0.0f,  // bottom right
        100.0f, 100.0f, 0.0f, 0.0f, // bottom left
        100.0f, 400.0f, 0.0f, 1.0f // top left
};
GLuint obj2_indices[] = {     // note that we start from 0
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
};

struct Object {
    Object(const void *vertices, const void *indices, const size_t vsize, const size_t isize,
           const VertexBufferLayout &layout, const GLenum indexType = GL_UNSIGNED_INT) :
            vao(), vbo(vertices, vsize), ebo(indexType, indices, isize) {
        vao.AddBuffer(vbo, layout);
    }

    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ebo;

    void Unbind() {
        ebo.Unbind();
        vbo.Unbind();
        vao.Unbind();
    }
};

namespace App {
    Renderer* renderer;

    Object* obj1;
    Object* obj2;
    Texture* tex1;
    Texture* tex2;
    Shader* shader;

    void setup(Window* window) {
        // Create Vertex Buffer Layout
        VertexBufferLayout layout;
        layout.Push<GL_FLOAT>(2); // Position
        layout.Push<GL_FLOAT>(2); // UV-Coord

        // Creating Object
        obj1 = new Object(obj1_vertices, obj1_indices, sizeof(obj1_vertices), sizeof(obj1_indices), layout);
        obj2 = new Object(obj2_vertices, obj2_indices, sizeof(obj2_vertices), sizeof(obj2_indices), layout);
        tex1 = new Texture(RESOURCES_PATH "/logo.jpg");
        tex2 = new Texture(RESOURCES_PATH "/hello.png");
        shader = new Shader(RESOURCES_PATH "/shader.glsl");

        // Create Renderer
        renderer = new Renderer();
        renderer->SetBlendType(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_FUNC_ADD);
        renderer->ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Binding Texture
        tex1->Bind(0);
        tex2->Bind(1);

        // Projection Matrix
        WindowSize wSize = window->GetSize();
        glm::mat4 projection = glm::ortho(0.0f, (float)wSize.w, 0.0f, (float)wSize.h, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, 0.0f));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 200.0f, 0.0f));
        glm::mat4 mvp = projection * view * model;

        shader->SetUniformMat4f("uMVP", mvp);
    }
    void render() {
        shader->SetUniform1i("u_Texture", 0);
        renderer->Draw((*obj1).vao, (*obj1).ebo, *shader);

        shader->SetUniform1i("u_Texture", 1);
        renderer->Draw((*obj2).vao, (*obj2).ebo, *shader);

        ImGuiIO& io = ImGui::GetIO();
        ImGui::Begin("Application Info");
        GLCall(ImGui::Text("OpenGL Version: %s", glGetString(GL_VERSION)));
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::End();

    }
    void stop() {
        delete shader;

        delete tex2, tex1;
        delete obj2, obj1;

        delete renderer;
    }
}

int main() {
    std::cout << "Info: Resources are loaded from '" << RESOURCES_PATH << '\'' << std::endl;
    Window window(1920,  1080, "Block Game", false, 3, 3);

    App::setup(&window);
    IMGUI_Setup(window.GetHandle());
    while (!window.ShouldClose()) {
        App::renderer->Clear();
        IMGUI_Render_BEFORE();

        App::render();

        IMGUI_Render_AFTER();
        window.SwapBuffers();
        Window::PollEvents();
    }
    IMGUI_Stop();
    App::stop();

    GLClearError();
    return 0;
}
