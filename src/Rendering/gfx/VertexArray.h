//
// Created by erikd on 20.04.2024.
// Refactored by erikd on 27.04.2024.

#pragma once
#include "GL.h"
#include "../../Defines.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout) const;

    void Bind() const;
    void Unbind() const;
private:
    uint32_t m_glId;
};
