//
// Created by erikd on 30.04.2024.
//

#pragma once
#include "GL.h"

namespace Engine::GL {
    struct IndexBuffer {
    public:
        inline explicit IndexBuffer(GLenum type) : m_id(0), m_type(type), m_size(0) {
            GLCall(glGenBuffers(1, &m_id));
            Bind();
        }
        inline IndexBuffer(GLenum type, void *data, size_t size, GLenum usage = GL_STATIC_DRAW) : m_id(0), m_type(type),
                                                                                                  m_size(0) {
            GLCall(glGenBuffers(1, &m_id));
            SetData(data, size, usage);
        }
        inline  ~IndexBuffer() {
            GLCall(glDeleteBuffers(1, &m_id));
        }

        inline void SetData(void *data, size_t size, GLenum usage = GL_STATIC_DRAW) {
            Bind();
            m_size = size;
            GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage));
        }
        inline void Bind() const {
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
        }
        static inline void Unbind() {
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        }

        [[nodiscard]] inline glid GetID() const {
            return m_id;
        }
        [[nodiscard]] inline GLenum GetType() const {
            return m_type;
        }
        [[nodiscard]] inline size_t GetSize() const {
            return m_size;
        }
        [[nodiscard]] inline size_t GetCount() const {
            return m_size / GL::GetSizeOfType(m_type);
        }
    protected:
        glid m_id;
        GLenum m_type;
        size_t m_size;
    };
}
