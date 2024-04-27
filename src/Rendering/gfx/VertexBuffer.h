//
// Created by erikd on 27.04.2024.
//

#pragma once
#include "GLBuffer.h"

class VertexBuffer: public GLBuffer<GL_ARRAY_BUFFER> {
public:
    explicit VertexBuffer(): GLBuffer<GL_ARRAY_BUFFER>() { }
    VertexBuffer(const void* data, size_t size, GLenum usage=GL_STATIC_DRAW): GLBuffer<GL_ARRAY_BUFFER>(data, size, usage) { }
};
