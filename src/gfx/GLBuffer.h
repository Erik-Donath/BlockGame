//
// Created by erikd on 20.04.2024.
//

#pragma once
#include "GL.h"

template <GLenum Buffer, GLenum Data>
class GLBuffer {
public:
    GLBuffer();
    GLBuffer(const void* data, size_t size, GLenum usage=GL_STATIC_DRAW);
    ~GLBuffer();

    void SetData(const void* data, size_t size, GLenum usage=GL_STATIC_DRAW);

    void Bind() const;
    void Unbind() const;

    [[nodiscard]] inline size_t GetSize() const {
        return m_size;
    }
    [[nodiscard]] inline size_t GetCount() const {
        //return m_size / GetSizeOfType(Data);
        return 6;
    }

    inline unsigned int GetGLId() {
        return m_glId;
    }
    inline GLenum GetBufferType() {
        return Buffer;
    }
    inline GLenum GetDataType() {
        return Data;
    }
private:
    unsigned int m_glId;
    size_t m_size;
};

template <GLenum Data>
using VertexBuffer = GLBuffer<GL_ARRAY_BUFFER, Data>;

template <GLenum Data>
using IndexBuffer = GLBuffer<GL_ELEMENT_ARRAY_BUFFER, Data>;