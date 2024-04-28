//
// Created by erikd on 20.04.2024.
// Refactored by erikd on 27.04.2024.

#pragma once
#include <string>
#include <unordered_map>

#include "../Defines.h"
#include "glm/glm.hpp"

#include "GL.h"

struct ShaderSource {
    std::string vertexSource;
    std::string fragmentSource;
    bool failed = false;
};

class Shader {
public:
    explicit Shader(const std::string& path);
    explicit Shader(const ShaderSource& source);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetInt(const std::string& name, int32_t v0);
    void SetFloat(const std::string& name, float v0);
    void SetVec1(const std::string& name, glm::vec1 v);
    void SetVec2(const std::string& name, glm::vec2 v);
    void SetVec3(const std::string& name, glm::vec3 v);
    void SetMat4(const std::string& name, glm::mat4 m);
    void SetSampler(const std::string& name, int32_t s);

    inline void Use() const {
        Bind();
    }
private:
    [[nodiscard]] int GetUniformLocation(const std::string& name);

    static ShaderSource ParseSourceFile(const std::string& filepath);
    static uint32_t CreateShaderProgram(const ShaderSource& source);
    static uint32_t CompileShader(GLenum type, const char* src);
    static const char* GetNameOfType(GLenum type);

    uint32_t m_glId;
    std::unordered_map<std::string, int32_t> m_uniformLocationCache;
};
