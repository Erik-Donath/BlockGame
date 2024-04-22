//
// Created by erikd on 22.04.2024.
//

#pragma once
#include <string>
#include "GL.h"

typedef unsigned char ubyte;

class Texture {
public:
    explicit Texture(const std::string& filepath);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    [[nodiscard]] inline unsigned int GetId() const {
        return m_glId;
    }
    [[nodiscard]] inline unsigned int GetWidth() const {
        return m_width;
    }
    [[nodiscard]] inline unsigned int GetHeight() const {
        return m_height;
    }
    [[nodiscard]] inline unsigned int GetBPP() const {
        return m_BPP;
    }
    [[nodiscard]] inline ubyte* GetLocalBuffer() const {
        return m_localBuffer;
    }
    [[nodiscard]] inline std::string GetFilepath() const {
        return m_filepath;
    }
private:
    unsigned int m_glId;

    int m_width, m_height, m_BPP;

    ubyte* m_localBuffer;
    std::string m_filepath;
};
