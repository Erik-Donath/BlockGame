//
// Created by erikd on 27.04.2024.
//

#pragma once
#include "../../Defines.h"
#include "GLBuffer.h"

class IndexBuffer: public GLBuffer<GL_ELEMENT_ARRAY_BUFFER> {
public:
    explicit IndexBuffer(GLenum dataType): GLBuffer<GL_ELEMENT_ARRAY_BUFFER>(), m_dataType(dataType) { }
    IndexBuffer(GLenum dataType, const void* data, size_t size, GLenum usage=GL_STATIC_DRAW): GLBuffer<GL_ELEMENT_ARRAY_BUFFER>(data, size, usage), m_dataType(dataType) { }

    [[nodiscard]] inline size_t GetCount() const {
        return m_size / GetSizeOfType(m_dataType);
    }
    [[nodiscard]] inline GLenum GetDataType() const {
        return m_dataType;
    }
protected:
    GLenum m_dataType;
};
