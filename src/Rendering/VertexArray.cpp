//
// Created by erikd on 20.04.2024.
// Refactored by erikd on 27.04.2024.

#include "VertexArray.h"

VertexArray::VertexArray(): m_glId(0) {
    GLCall(glGenVertexArrays(1, &m_glId));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &m_glId));
}

void VertexArray::AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout &layout) const {
    Bind();
    vbo.Bind();

    size_t offset = 0;
    const std::vector<VertexBufferElement> &elements = layout.GetElements();
    for(unsigned int i = 0; i < elements.size(); i++) {
        const VertexBufferElement& element = elements[i];

        GLCall(glVertexAttribPointer(i, (int32_t)element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE, (int32_t)layout.GetStride(), (const void*)offset));
        GLCall(glEnableVertexAttribArray(i));
        offset += element.count * GetSizeOfType(element.type);
    }
    Unbind();
}

void VertexArray::Bind() const {
    GLCall(glBindVertexArray(m_glId));
}


void VertexArray::Unbind() const {
    GLCall(glBindVertexArray(0));
}
