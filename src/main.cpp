#include <iostream>
#include "base/GFX.h"
#include "base/Renderer.h"

float obj1_vertices[] = {
         0.5f,  0.5f, 1.0f, 1.0f,   // top right
         0.5f, -0.5f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f // top left
};
GLuint obj1_indices[] = {     // note that we start from 0
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
};

struct Object {
    Object(const void* vertices, const void* indices, const size_t vsize, const size_t isize, const VertexBufferLayout& layout, const GLenum indexType = GL_UNSIGNED_INT):
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
    Window window(800, 600, "Block Game", false, 4, 6);

    VertexBufferLayout layout;
    layout.Push<GL_FLOAT>(2); // Position
    layout.Push<GL_FLOAT>(2); // UV-Coord


    Object obj1(obj1_vertices, obj1_indices, sizeof(obj1_vertices), sizeof(obj1_indices), layout);
    Shader shader(RESOURCES_PATH "/shader.glsl");
    Texture texture(RESOURCES_PATH "/logo.jpg");

    // Unbind everything
    obj1.Unbind();
    shader.Unbind();
    texture.Unbind();
    GLClearError();

    Renderer renderer;
    renderer.ClearColor();

    while (!window.ShouldClose()) {
        renderer.Clear();

        texture.Bind(0);
        shader.SetUniform1i("u_Texture", 0);
        renderer.Draw(obj1.vao, obj1.ebo, shader);

        window.SwapBuffers();
        Window::PollEvents();
    }

    GLClearError();
    return 0;
}
