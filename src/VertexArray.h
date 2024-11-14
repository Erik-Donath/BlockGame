//
// Created by erikd on 12.11.2024.
//

#pragma once
#include <cstdint>
#include <vector>
#include <memory>

#include "Buffer.h"
#include "GL.h"

struct VertexAttribute {
public:
    VertexAttribute(GLenum type, int32_t length, bool normalized = false): Type(type), Length(length), Normalized(normalized) { }
    const GLenum Type;
    const int32_t Length;
    const bool Normalized;
};

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const std::shared_ptr<ArrayBuffer>& buffer, const std::vector<VertexAttribute>& attributes);
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer);

    void Bind() const;
    static void Unbind();

    [[nodiscard]] inline glid GetId() const {
        return m_id;
    }
private:
    glid m_id;
    std::vector<std::shared_ptr<ArrayBuffer>> m_vertexBuffers;
    std::shared_ptr<IndexBuffer> m_indexBuffer;
};
