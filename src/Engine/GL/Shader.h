//
// Created by erikd on 30.04.2024.
//
#pragma once
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"
#include "GL.h"

namespace Engine::GL {
    class Shader {
    public:
        Shader(const std::string &vertex, const std::string &fragment);
        ~Shader();

        void SetInt(const std::string &name, int32_t v0);
        void SetFloat(const std::string &name, float v0);
        void SetVec1(const std::string &name, glm::vec1 v);
        void SetVec2(const std::string &name, glm::vec2 v);
        void SetVec3(const std::string &name, glm::vec3 v);
        void SetMat4(const std::string &name, glm::mat4 m);
        void SetSampler(const std::string &name, int32_t s);
        i32 GetLocation(const std::string &name);

        inline void Bind() const {
            GLCall(glUseProgram(m_id));
        }

        static inline void Unbind() {
            GLCall(glUseProgram(0));
        }

        inline void Use() const {
            Bind();
        }

    protected:
        glid m_id;
        std::unordered_map<std::string, i32> m_locations;

        static glid CompileShader(GLenum type, cstr source);
    };
}
