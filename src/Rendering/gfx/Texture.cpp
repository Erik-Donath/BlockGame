//
// Created by erikd on 22.04.2024.
// Refactored by erikd on 27.04.2024.

#include <iostream>
#include "stb/stb_image.h"

#include "GL.h"
#include "Texture.h"

static int32_t s_maxTextureSlot = 0;

Texture::Texture(const std::string& filepath): m_glId(0), m_width(0), m_height(0), m_BPP(1), m_filepath(filepath) {
    stbi_set_flip_vertically_on_load(1);
    unsigned char* m_localBuffer = stbi_load(filepath.c_str(), &m_width, &m_height, &m_BPP, 4);

    if(!m_localBuffer) {
        std::cerr << "Error: Failed to load file '" << filepath << '\'' << std::endl;
        return;
    }

    if(!s_maxTextureSlot) {
        GLCall(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &s_maxTextureSlot));
        std::cout << "Info: Max Texture Slots are " << s_maxTextureSlot << std::endl;
    }

    GLCall(glGenTextures(1, &m_glId));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_glId));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    stbi_image_free(m_localBuffer);
}

Texture::~Texture() {
    GLCall(glDeleteTextures(1, &m_glId));
}

void Texture::Bind(unsigned int slot) const {
    if(slot > s_maxTextureSlot) {
        std::cerr << "Warning: Tried to Bind Texture(" << m_glId << ") '" << m_filepath << "' to slot " << slot << std::endl;
        return;
    }

    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_glId));
}

void Texture::Unbind() const {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
