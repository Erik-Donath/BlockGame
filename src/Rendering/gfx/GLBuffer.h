//
// Created by erikd on 20.04.2024.
// Refactored by erikd on 27.04.2024.

#pragma once
#include "../../Defines.h"
#include "GL.h"

template <GLenum Buffer>
class GLBuffer {
public:
    GLBuffer(): m_glId(0), m_size(0) {
        GLCall(glGenBuffers(1, &m_glId));
    }
    GLBuffer(const void* data, size_t size, GLenum usage=GL_STATIC_DRAW): m_glId(0), m_size(0) {
        GLCall(glGenBuffers(1, &m_glId));
        SetData(data, size, usage);
    }
    ~GLBuffer() {
        GLCall(glDeleteBuffers(1, &m_glId));
    }

    void SetData(const void* data, size_t size, GLenum usage=GL_STATIC_DRAW) {
        Bind();

        GLCall(glBufferData(Buffer, size, data, usage));
        m_size = size;

        Unbind();
    }

    void Bind() const {
        GLCall(glBindBuffer(Buffer, m_glId));
    }
    void Unbind() const {
        GLCall(glBindBuffer(Buffer, 0));
    }

    [[nodiscard]] inline size_t GetSize() const {
        return m_size;
    }

    [[nodiscard]] inline unsigned int GetGLId() const {
        return m_glId;
    }
    [[nodiscard]] inline GLenum GetBufferType() const {
        return Buffer;
    }
protected:
    uint32_t m_glId;
    size_t m_size;
};