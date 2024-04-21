//
// Created by erikd on 20.04.2024.
//

#pragma once
#include "GL.h"
#include "GLBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout) const;

    void Bind() const;
    void Unbind() const;

    explicit operator unsigned int() const {
        return m_glId;
    }
private:
    unsigned int m_glId;
};

