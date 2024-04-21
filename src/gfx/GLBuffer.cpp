//
// Created by erikd on 20.04.2024.
//

#include "GL.h"
#include "GLBuffer.h"

template<GLenum Buffer, GLenum Data>
GLBuffer<Buffer, Data>::GLBuffer(): m_glId(0), m_size(0) {
    GLCall(glGenBuffers(1, &m_glId));
}

template<GLenum Buffer, GLenum Data>
GLBuffer<Buffer, Data>::GLBuffer(const void *data, size_t size, GLenum usage): m_glId(0), m_size(0) {
    GLCall(glGenBuffers(1, &m_glId));
    SetData(data, size, usage);
}

template<GLenum Buffer, GLenum Data>
GLBuffer<Buffer, Data>::~GLBuffer() {
    GLCall(glDeleteBuffers(1, &m_glId));
}

template<GLenum Buffer, GLenum Data>
void GLBuffer<Buffer, Data>::Bind() const {
    GLCall(glBindBuffer(Buffer, m_glId));
}

template<GLenum Buffer, GLenum Data>
void GLBuffer<Buffer, Data>::Unbind() const {
    GLCall(glBindBuffer(Buffer, 0));
}

template<GLenum Buffer, GLenum Data>
void GLBuffer<Buffer, Data>::SetData(const void *data, size_t size, GLenum usage) {
    Bind();
    GLCall(glBufferData(Buffer, size, data, usage));
    m_size = size;
    Unbind();
}
