//
// Created by erikd on 30.04.2024.
//

#include "VertexArray.h"

VertexArray::VertexArray(): m_id(0) {
    GLCall(glGenVertexArrays(1, &m_id));
    Bind();
}
VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &m_id));
}
VertexArray::AddBuffer(const VertexBuffer& buffer) {
    Bind();
    buffer.Bind();

    size_t offset = 0;
    const auto& elements = buffer.GetElements();
    for(size_t i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];

        GLCall(glVertexAttribPointer(i, (int32_t)element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE, (int32_t)layout.GetStride(), (const void*)offset));
        GLCall(glEnableVertexAttribArray(i));
        offset += element.count * GetSizeOfType(element.type);
    }
}