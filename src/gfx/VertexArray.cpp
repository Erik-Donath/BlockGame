//
// Created by erikd on 20.04.2024.
//

#include "GL.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray(): m_glId(0) {
    GLCall(glGenVertexArrays(1, &m_glId));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &m_glId));
}

void VertexArray::AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout &layout) const {
    Bind();
    vbo.Bind();

    const std::vector<VertexBufferElement> &elements = layout.GetElements();
    unsigned long long int offset = 0;
    for(unsigned int i = 0; i < elements.size(); i++) {
        const VertexBufferElement& element = elements[i];

        GLCall(glVertexAttribPointer(i, (int)element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE, (int)layout.GetStride(), (const void*)offset));
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
