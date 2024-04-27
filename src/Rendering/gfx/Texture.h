//
// Created by erikd on 22.04.2024.
// Refactored by erikd on 27.04.2024.

#pragma once
#include <string>

#include "../../Defines.h"
#include "GL.h"

class Texture {
public:
    explicit Texture(const std::string& filepath);
    ~Texture();

    void Bind(uint32_t slot = 0) const;
    void Unbind() const;

    [[nodiscard]] inline uint32_t GetId() const {
        return m_glId;
    }
    [[nodiscard]] inline uint32_t GetWidth() const {
        return m_width;
    }
    [[nodiscard]] inline uint32_t GetHeight() const {
        return m_height;
    }
    [[nodiscard]] inline uint32_t GetBPP() const {
        return m_BPP;
    }
    [[nodiscard]] inline std::string GetFilepath() const {
        return m_filepath;
    }
private:
    uint32_t m_glId;

    int32_t m_width, m_height, m_BPP;
    std::string m_filepath;
};
