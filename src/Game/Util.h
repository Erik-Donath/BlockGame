//
// Created by erikd on 12.11.2024.
//

#pragma once
#include "glm/glm.hpp"

constexpr glm::vec3 WorldUp = glm::vec3(0, 1, 0);

namespace std {
    template<> struct hash<glm::ivec2> {
        std::size_t operator()(const glm::ivec2& v) const noexcept {
            return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
        }
    };
}
