#include <iostream>
#include "base/GFX.h"
#include "base/Renderer.h"

const char* vs_src = "#version 330 core\nlayout (location = 0) in vec4 aPos;\nvoid main() {\n   gl_Position = aPos;\n}\0";
const char* fs_src = "#version 330 core\nout vec4 FragColor;\nvoid main() {\n   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n}\0";

float vertices[] = {
        0.5f, 0.5f,   // top right
        0.5f, -0.5f,  // bottom right
        -0.5f,-0.5f,  // bottom left
        -0.5f,0.5f    // top left
};
GLubyte indices[] = {     // note that we start from 0
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
};

int main() {
    Window window(800, 600, "Hello CMake");

    VertexArray vao;
    VertexBuffer vbo(vertices, sizeof(vertices));

    VertexBufferLayout vbol;
    vbol.Push<GL_FLOAT>(2);
    vao.AddBuffer(vbo, vbol);

    IndexBuffer ebo(GL_UNSIGNED_BYTE, indices, sizeof(indices));
    Shader shader({vs_src, fs_src, false });

    // Unbind everything
    vbo.Unbind();
    ebo.Unbind();
    vao.Unbind();
    shader.Unbind();
    GLClearError();

    Renderer renderer;
    renderer.ClearColor();
    while (!window.ShouldClose()) {
        Window::PollEvents();

        renderer.Clear();
        renderer.Draw(vao, ebo, shader);

        window.SwapBuffers();
    }

    GLClearError();
    return 0;
}
