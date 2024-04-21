//
// Created by erikd on 20.04.2024.
//

#pragma once
#include <vector>

#include "GL.h"
#include "GLBuffer.h"

struct VertexBufferElement {
    GLenum type;
    unsigned int count;
    bool normalized;
};

class VertexBufferLayout {
public:
    VertexBufferLayout() : m_stride(0) { }

    template<GLenum T>
    void Push(unsigned int count) {
        m_elements.push_back({ T, count, false });
        m_stride += count * GetSizeOfType(T);
    }

    [[nodiscard]] inline unsigned int GetStride() const {
        return m_stride;
    }
    [[nodiscard]] inline const std::vector<VertexBufferElement>& GetElements() const {
        return m_elements;
    }
private:
    unsigned int m_stride = 0;
    std::vector<VertexBufferElement> m_elements;
};