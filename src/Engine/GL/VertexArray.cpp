//
// Created by erikd on 30.04.2024.
//

#include "VertexArray.h"
using namespace Engine::GL;

VertexArray::VertexArray(): m_id(0) {
    GLCall(glGenVertexArrays(1, &m_id));
}
VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &m_id));
}
void VertexArray::AddBuffer(const VertexBuffer &buffer) const {
    Bind();
    buffer.Bind();

    size_t offset = 0, stride = 0;
    const auto& elements = buffer.GetElements();

    for(auto& element : elements) {
        stride += element.count * GL::GetSizeOfType(element.type);
    }

    for(size_t i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];

        GLCall(glVertexAttribPointer(i, (int32_t)element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE, (int32_t)stride, (const void*)offset));
        GLCall(glEnableVertexAttribArray(i));
        offset += element.count * GL::GetSizeOfType(element.type);
    }
    Unbind();
}

void VertexArray::AddBuffer(const IndexBuffer &buffer) const {
    Bind();
    buffer.Bind();
    Unbind();
}
