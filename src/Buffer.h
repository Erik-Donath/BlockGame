//
// Created by erikd on 19.10.2024.
//

#pragma once
#include "GL.h"

#include <iostream>

template <GLenum BufferType>
struct Buffer {
public:
    Buffer() {
        GLCall(glGenBuffers(1, &m_id));
        Bind();

        std::cout << "Created Buffer<" << m_id << "> as " << BufferType << std::endl;
    }
    Buffer(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW) {
        GLCall(glGenBuffers(1, &m_id));
        Set(data, size, usage);

        std::cout << "Created Buffer<" << m_id << "> as " << BufferType << std::endl;
    }
    ~Buffer() {
        GLCall(glDeleteBuffers(1, &m_id));

        std::cout << "Deleted Buffer<" << m_id << ">" << std::endl;
    }

    void Bind() const {
        GLCall(glBindBuffer(BufferType, m_id));
    }
    static void Unbind() {
        GLCall(glBindBuffer(BufferType, 0));
    }

    void Set(const void* data, size_t size, GLenum usage = GL_STATIC_DRAW) {
        Bind();
        GLCall(glBufferData(BufferType, size, data, usage));
        m_size = size;
        m_data = data;
    }
    [[nodiscard]] inline const void* Get() const {
        return m_data;
    }

    [[nodiscard]] inline glid GetId() const {
        return m_id;
    }
    [[nodiscard]] inline size_t GetSize() const {
        return m_size;
    }
    [[nodiscard]] inline GLenum GetBufferType() const {
        return BufferType;
    }
protected:
    glid m_id = 0;
    size_t m_size = 0;
    const void* m_data = nullptr;
};

typedef Buffer<GL_ARRAY_BUFFER> ArrayBuffer;
typedef Buffer<GL_ELEMENT_ARRAY_BUFFER> IndexBuffer;
