#include <iostream>
#include "base/GFX.h"
#include "base/Renderer.h"

const char* vs_src = "#version 330 core\nlayout (location = 0) in vec4 aPos;\nout vec4 vPos;\nvoid main() {\n    vPos = aPos;\n    gl_Position = aPos;\n}\0";
const char* fs_src = "#version 330 core\nin vec4 vPos;\nout vec4 FragColor;\nvoid main() {\n    FragColor = vec4((vPos.r + 1) / 2, (vPos.g + 1) / 2, 0.0f, 1.0f);\n}\0";

float obj_vertices[] = {
        0.5f, 0.5f,   // top right
        0.5f, -0.5f,  // bottom right
        -0.5f,-0.5f,  // bottom left
        -0.5f,0.5f    // top left
};
GLuint obj_indices[] = {     // note that we start from 0
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
    Window window(800, 600, "Block Game");

    VertexBufferLayout layout;
    layout.Push<GL_FLOAT>(2);
    Obj obj(obj_vertices, obj_indices, sizeof(obj_vertices), sizeof(obj_indices), layout);
    Shader shader({vs_src, fs_src, false });

    // Unbind everything
    obj.Unbind();
    shader.Unbind();
    GLClearError();

    Renderer renderer;
    renderer.ClearColor();

    while (!window.ShouldClose()) {
        renderer.Clear();
        renderer.Draw(obj.vao, obj.ebo, shader);

        window.SwapBuffers();
        Window::PollEvents();
    }

    GLClearError();
    return 0;
}
