//
// Created by erikd on 21.04.2024.
//

#include "../GFX.h"
#include "Renderer.h"

void Renderer::Clear() const {
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::ClearColor(float r, float g, float b, float a) const {
    GLCall(glClearColor(r, g, b, a));
}

void Renderer::Draw(const VertexArray &vao, const IndexBuffer &ebo, const Shader &shader) const {
    vao.Bind();
    ebo.Bind();
    shader.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ebo.GetCount(), ebo.GetDataType(), nullptr));
}

void Renderer::SetBlendType(GLenum src, GLenum dst, GLenum func) const {
    GLCall(glBlendFunc(src, dst));
    GLCall(glBlendEquation(func));
    GLCall(glEnable(GL_BLEND));
}
