//
// Created by erikd on 30.04.2024.
//

#pragma once
#include <string>
#include <glm/glm.hpp>
#include "GL.h"

namespace Rendering {
    class Texture {
    public:
        explicit Texture(const std::string &path);

        ~Texture();

        void Bind(u32 slot = 0) const;

        static void Unbind();

        [[nodiscard]] inline uint32_t GetId() const {
            return m_id;
        }

        [[nodiscard]] inline glm::ivec2 GetSize() const {
            return m_size;
        }

        [[nodiscard]] inline uint32_t GetWidth() const {
            return m_size.x;
        }

        [[nodiscard]] inline uint32_t GetHeight() const {
            return m_size.y;
        }

        [[nodiscard]] inline uint32_t GetBPP() const {
            return m_bpp;
        }

        [[nodiscard]] inline std::string GetPath() const {
            return m_path;
        }

    protected:
        glid m_id;

        i32 m_bpp;
        glm::ivec2 m_size;

        std::string m_path;

        static i32 s_max_slots;
    };
}