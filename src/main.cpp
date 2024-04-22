#include <iostream>
#include "base/GFX.h"
#include "base/Renderer.h"

float obj1_vertices[] = {
        -0.55f, -0.55f,   // top right
        -1.0f, -1.0f,  // bottom right
        -0.75f,0.75f,  // bottom left
};
GLuint obj1_indices[] = {     // note that we start from 0
        0, 1, 2,   // first triangle
};

float obj2_vertices[] = {
        0.5f, 0.5f,   // top right
        0.5f, -0.5f,  // bottom right
        -0.5f,-0.5f,  // bottom left
        -0.5f,0.5f    // top left
};
GLuint obj2_indices[] = {     // note that we start from 0
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
};

struct Obj {
    Obj(const void* vertices, const void* indices, const size_t vsize, const size_t isize, const VertexBufferLayout& layout, const GLenum indexType = GL_UNSIGNED_INT):
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

int main() {
    std::cout << "Info: Resources are loaded from '" << RESOURCES_PATH << '\'' << std::endl;
    Window window(800, 600, "Block Game");

    VertexBufferLayout layout;
    layout.Push<GL_FLOAT>(2);


    Obj obj1(obj1_vertices, obj1_indices, sizeof(obj1_vertices), sizeof(obj1_indices), layout);
    Obj obj2(obj2_vertices, obj2_indices, sizeof(obj2_vertices), sizeof(obj2_indices), layout);

    Shader shader(RESOURCES_PATH "/shader.glsl");

    // Unbind everything
    obj1.Unbind();
    obj2.Unbind();
    shader.Unbind();
    GLClearError();

    Renderer renderer;
    renderer.ClearColor();

    while (!window.ShouldClose()) {
        renderer.Clear();
        renderer.Draw(obj1.vao, obj1.ebo, shader);
        renderer.Draw(obj2.vao, obj2.ebo, shader);

        window.SwapBuffers();
        Window::PollEvents();
    }

    GLClearError();
    return 0;
}
