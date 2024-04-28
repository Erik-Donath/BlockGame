//
// Created by erikd on 20.04.2024.
// Refactored by erikd on 27.04.2024.

#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <iostream>

#include "GL.h"
#include "Shader.h"

Shader::Shader(const std::string& path): m_glId(0) {
    ShaderSource source = ParseSourceFile(path);

    if(source.failed) return;
    m_glId = CreateShaderProgram(source);
}

Shader::Shader(const ShaderSource& source): m_glId(0) {
    m_glId = CreateShaderProgram(source);
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_glId));
}

void Shader::Bind() const {
    GLCall(glUseProgram(m_glId));
}

void Shader::Unbind() const {
    GLCall(glUseProgram(0));
}

int32_t Shader::GetUniformLocation(const std::string& name) {
    if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];

    GLCall(int32_t location = glGetUniformLocation(m_glId, name.c_str()));
    if(location == -1)
        std::cout << "Warning: Uniform '" << name << "' does not exist" << std::endl;

    m_uniformLocationCache[name] = location;
    return location;
}

ShaderSource Shader::ParseSourceFile(const std::string& filepath) {
    std::ifstream stream(filepath);
    if(stream.fail()) {
        std::cerr << "Error: Failed to open file '" << filepath << "'" << std::endl;
        return {"", "", true};
    }

    uint32_t shaderType = -1;
    std::stringstream source[2];

    std::string line;
    while (std::getline(stream, line)) {
        if(line.rfind("#shader ", 0) == 0) {
            if(line == "#shader none") shaderType = -1;
            if(line == "#shader vertex") shaderType = 0;
            if(line == "#shader fragment") shaderType = 1;
            continue;
        }

        if(shaderType > 1) continue;
        source[shaderType] << line << '\n';
    }
    return { source[0].str(), source[1].str(), false };
}

uint32_t Shader::CreateShaderProgram(const ShaderSource& source) {
    uint32_t vertexShaderId = CompileShader(GL_VERTEX_SHADER, source.vertexSource.c_str());
    uint32_t fragmentShaderId = CompileShader(GL_FRAGMENT_SHADER, source.fragmentSource.c_str());

    if(!vertexShaderId || !fragmentShaderId) {
        return 0;
    }

    GLCall(uint32_t id = glCreateProgram());
    GLCall(glAttachShader(id, vertexShaderId));
    GLCall(glAttachShader(id, fragmentShaderId));

    GLCall(glLinkProgram(id));
    GLCall(glValidateProgram(id));

    GLCall(glDeleteShader(vertexShaderId));
    GLCall(glDeleteShader(fragmentShaderId));

    return id;
}

uint32_t Shader::CompileShader(GLenum type, const char* src) {
    GLCall(uint32_t id = glCreateShader(type));

    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int32_t success;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
    if(!success) {
        int32_t length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

        char* msg = new char[length];
        GLCall(glGetShaderInfoLog(id, length, &length, msg));

        std::cerr << "Error: Failed to compile " << GetNameOfType(type) << " Shader: " << std::endl << msg << std::endl;
        delete[] msg;

        GLCall(glDeleteShader(id));
        id = 0;
    }
    return id;
}

const char* Shader::GetNameOfType(GLenum type) {
    switch (type) {
        case GL_VERTEX_SHADER: return "vertex";
        case GL_FRAGMENT_SHADER: return "fragment";
        default: return "unknown";
    }
}

void Shader::SetInt(const std::string &name, int32_t v0) {
    Bind();
    GLCall(glUniform1i(GetUniformLocation(name), v0));
}
void Shader::SetFloat(const std::string &name, float v0) {
    Bind();
    GLCall(glUniform1f(GetUniformLocation(name), v0));
}

void Shader::SetVec1(const std::string &name, glm::vec1 v) {
    Bind();
    GLCall(glUniform1fv(GetUniformLocation(name), 1, &v.x));
}
void Shader::SetVec2(const std::string &name, glm::vec2 v) {
    Bind();
    GLCall(glUniform2fv(GetUniformLocation(name), 1, &v.x));
}
void Shader::SetVec3(const std::string &name, glm::vec3 v) {
    Bind();
    GLCall(glUniform3fv(GetUniformLocation(name), 1, &v.x));
}
void Shader::SetMat4(const std::string &name, glm::mat4 m) {
    Bind();
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &m[0][0]));
}

void Shader::SetSampler(const std::string& name, int32_t s) {
    Bind();
    GLCall(glUniform1i(GetUniformLocation(name), s));
}
