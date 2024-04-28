//
// Created by erikd on 20.04.2024.
// Refactored by erikd on 27.04.2024.

#pragma once
#include <vector>

#include "GL.h"
#include "../Defines.h"
#include "VertexBuffer.h"

struct VertexBufferElement {
    GLenum type;
    uint32_t count;
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
    void Pop() {
        VertexBufferElement element = m_elements.back();
        m_stride -= element.count * GetSizeOfType(element.type);
        m_elements.pop_back();
    }

    [[nodiscard]] inline uint32_t GetStride() const {
        return m_stride;
    }
    [[nodiscard]] inline const std::vector<VertexBufferElement>& GetElements() const {
        return m_elements;
    }
private:
    uint32_t m_stride = 0;
    std::vector<VertexBufferElement> m_elements;
};
