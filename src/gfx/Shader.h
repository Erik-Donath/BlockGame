//
// Created by erikd on 20.04.2024.
//

#pragma once
#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

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

    void SetUniform1i(const std::string& name, int v0);
    void SetUniform1f(const std::string& name, float v0);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const std::string& name, const glm::mat4 matrix);
    inline void Use() const {
        Bind();
    }
private:
    [[nodiscard]] int GetUniformLocation(const std::string& name);

    static ShaderSource ParseSourceFile(const std::string& filepath);
    static unsigned int CreateShaderProgram(const ShaderSource& source);
    static unsigned int CompileShader(GLenum type, const char* src);
    static const char* GetNameOfType(GLenum type);

    unsigned int m_glId;
    std::unordered_map<std::string, int> m_uniformLocationCache;
};
