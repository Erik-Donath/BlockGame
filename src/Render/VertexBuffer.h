//
// Created by erikd on 30.04.2024.
//

#pragma once
#include <vector>
#include "GL.h"

struct VertexBufferElement {
    GLenum type;
    u32 count;
    bool normalized;
};

struct VertexBuffer {
public:
    inline VertexBuffer(): m_id(0), m_size(0) {
        GLCall(glGenBuffers(1, &m_id));
        Bind();
    }
    inline VertexBuffer(void* data, size_t size, GLenum usage = GL_STATIC_DRAW): m_id(0), m_size(0) {
        GLCall(glGenBuffers(1, &m_id));
        SetData(data, size, usage);
    }
    inline  ~VertexBuffer() {
        GLCall(glDeleteBuffers(1, &m_id));
    }
    inline void SetData(void* data, size_t size, GLenum usage = GL_STATIC_DRAW) {
        Bind();
        m_size = size;
        GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
    }
    inline void Bind() const {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
    }
    static inline void Unbind() {
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }
    void SetLayout(const std::vector<VertexBufferElement>& elements) {
        m_elements = elements;
    }
    [[nodiscard]] inline glid GetID() const {
        return m_id;
    }
    [[nodiscard]] inline size_t GetSize() const {
        return m_size;
    }
    [[nodiscard]] inline const std::vector<VertexBufferElement>& GetElements() const {
        return m_elements;
    }
protected:
    glid m_id;
    size_t m_size;
    std::vector<VertexBufferElement> m_elements;
};
