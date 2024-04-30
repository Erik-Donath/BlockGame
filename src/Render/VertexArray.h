//
// Created by erikd on 30.04.2024.
//

#pragma once
#include "GL.h"
#include "VertexBuffer.h"

struct VertexArray {
public:
    VertexArray();
    ~VertexArray();
    void AddBuffer(const VertexBuffer& buffer);

    void Bind() const;
    void Unbind() const;
protected:
    glid m_id;
};
