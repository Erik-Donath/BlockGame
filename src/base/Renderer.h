//
// Created by erikd on 21.04.2024.
//

#pragma once
#include "GFX.h"

class Renderer {
public:
    template<GLenum DataType>
    void Draw(const VertexArray& vao, const IndexBuffer<DataType>& ebo, const Shader& shader) const;
private:
};
