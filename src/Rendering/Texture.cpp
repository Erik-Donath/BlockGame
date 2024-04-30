//
// Created by erikd on 30.04.2024.
//

#include <iostream>
#include <stb/stb_image.h>
#include "Texture.h"

using namespace Rendering;

int Texture::s_max_slots = 0;

Texture::Texture(const std::string &path): m_id(0), m_bpp(0), m_size(0, 0), m_path(path) {
    stbi_set_flip_vertically_on_load(1);
    byte* buffer = stbi_load(path.c_str(), &m_size.x, &m_size.y, &m_bpp, 4);

    if(!buffer) {
        std::cerr << "Error: Failed to load file '" << path << '\'' << std::endl;
        m_id = 0;
        return;
    }

    if(!s_max_slots) {
        GLCall(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &s_max_slots));
        std::cout << "Info: Max Texture Slots are " << s_max_slots << std::endl;
    }

    GLCall(glGenTextures(1, &m_id));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_id));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_size.x, m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    stbi_image_free(buffer);
}

Texture::~Texture() {
    GLCall(glDeleteTextures(1, &m_id));
}

void Texture::Bind(u32 slot) const {
    if(slot > s_max_slots) {
        std::cerr << "Warning: Tried to Bind Texture(" << m_id << ") '" << m_path << "' to slot " << slot << std::endl;
        return;
    }

    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_id));
}

void Texture::Unbind() {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
