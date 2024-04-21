//
// Created by erikd on 21.04.2024.
//

#include "GFX.h"
#include "Renderer.h"

void Renderer::Draw(const VertexArray &vao, const IndexBuffer &ebo, const Shader &shader) const {
    vao.Bind();
    ebo.Bind();
    shader.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ebo.GetCount(), ebo.GetDataType(), nullptr));
}