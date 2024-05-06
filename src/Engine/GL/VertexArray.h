//
// Created by erikd on 30.04.2024.
//

#pragma once
#include "GL.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Engine::GL {
    struct VertexArray {
    public:
        VertexArray();
        ~VertexArray();
        void AddBuffer(const VertexBuffer &buffer) const;
        void AddBuffer(const IndexBuffer &buffer)  const;

        inline void Bind() const {
            GLCall(glBindVertexArray(m_id));
        }

        static inline void Unbind() {
            GLCall(glBindVertexArray(0));
        }

        [[nodiscard]] inline glid GetId() const {
            return m_id;
        }

    protected:
        glid m_id;
    };
}
