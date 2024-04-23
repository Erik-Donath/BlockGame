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
float obj2_vertices[] = {
        0.25f,  0.55f, 1.0f, 1.0f,   // top right
        0.25f, 0.05f, 1.0f, 0.0f,  // bottom right
        -0.25f, 0.05f, 0.0f, 0.0f, // bottom left
        -0.25f, 0.55f, 0.0f, 1.0f // top left
};
GLuint obj2_indices[] = {     // note that we start from 0
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
    Window window(1920,  1080, "Block Game", true, 3, 3);

    // Enabling Blending
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    // Create Vertex Buffer Layout
    VertexBufferLayout layout;
    layout.Push<GL_FLOAT>(2); // Position
    layout.Push<GL_FLOAT>(2); // UV-Coord

    // Creating Object
    Object obj1(obj1_vertices, obj1_indices, sizeof(obj1_vertices), sizeof(obj1_indices), layout);
    Object obj2(obj2_vertices, obj2_indices, sizeof(obj2_vertices), sizeof(obj2_indices), layout);
    Texture texture1(RESOURCES_PATH "/logo.jpg");
    Texture texture2(RESOURCES_PATH "/hello.png");
    Shader shader(RESOURCES_PATH "/shader.glsl");

    // Unbind everything & Clearing Errors
    obj1.Unbind();
    obj2.Unbind();
    texture1.Unbind();
    texture2.Unbind();
    shader.Unbind();
    GLClearError();

    // Create Renderer
    Renderer renderer;
    renderer.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Binding Texture
    texture1.Bind(0);
    texture2.Bind(1);

    while (!window.ShouldClose()) {
        renderer.Clear();

        shader.SetUniform1i("u_Texture", 0);
        renderer.Draw(obj1.vao, obj1.ebo, shader);

        shader.SetUniform1i("u_Texture", 1);
        renderer.Draw(obj2.vao, obj2.ebo, shader);

        window.SwapBuffers();
        Window::PollEvents();
    }

    GLClearError();
    return 0;
}
