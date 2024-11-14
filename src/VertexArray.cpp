//
// Created by erikd on 12.11.2024.
//

#include "VertexArray.h"

VertexArray::VertexArray(): m_id(0) {
    GLCall(glGenVertexArrays(1, &m_id));
    std::cout << "Created Vertex Array<" << m_id << ">" << std::endl;
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &m_id));
    std::cout << "Deleted Vertex Array<" << m_id << ">" << std::endl;
}

void VertexArray::AddBuffer(const std::shared_ptr<ArrayBuffer> &buffer, const std::vector<VertexAttribute> &attributes) {
    Bind();
    buffer->Bind();

    uint32_t stride = 0;
    for(const VertexAttribute& att: attributes) {
        stride += att.Length * SizeofGLType(att.Type);
    }

    uint32_t index = 0;
    intptr_t offset = 0;
    for(const VertexAttribute& attr: attributes) {
        GLCall(glVertexAttribPointer(index, attr.Length, attr.Type, attr.Normalized, stride, (void*)offset));
        GLCall(glEnableVertexAttribArray(index));
        offset += (intptr_t)(attr.Length * SizeofGLType(attr.Type));
        index++;
    }

    m_vertexBuffers.push_back(buffer);
    Unbind();
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &buffer) {
    Bind();
    buffer->Bind();
    m_indexBuffer = buffer;
    Unbind();
}

void VertexArray::Bind() const {
    GLCall(glBindVertexArray(m_id));
}

void VertexArray::Unbind() {
    GLCall(glBindVertexArray(0));
}
