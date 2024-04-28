//
// Created by erikd on 21.04.2024.
//

#pragma once
#include "GFX.h"

class Renderer {
public:
    void Clear() const;
    void ClearColor(float r = 0.2f, float g = 0.3f, float b = 0.3f, float a = 1.0f) const;
    void Draw(const VertexArray& vao, const IndexBuffer& ebo, const Shader& shader) const;

    void SetBlendType(GLenum src, GLenum dst, GLenum func) const;
private:
};
