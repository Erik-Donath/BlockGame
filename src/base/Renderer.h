//
// Created by erikd on 21.04.2024.
//

#pragma once
#include "GFX.h"

class Renderer {
public:
    void Draw(const VertexArray& vao, const IndexBuffer& ebo, const Shader& shader) const;
private:
};
