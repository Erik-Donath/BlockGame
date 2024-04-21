//
// Created by erikd on 20.04.2024.
//

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

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    Bind();
    GLCall(glUniform4f(GetUniformLocation(name), v0 , v1, v2, v3));
    Unbind();
}

int Shader::GetUniformLocation(const std::string& name) {
    if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
        return m_uniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_glId, name.c_str()));
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

    unsigned int shaderType = -1;
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

unsigned int Shader::CreateShaderProgram(const ShaderSource& source) {
    unsigned int vertexShaderId = CompileShader(GL_VERTEX_SHADER, source.vertexSource.c_str());
    unsigned int fragmentShaderId = CompileShader(GL_FRAGMENT_SHADER, source.fragmentSource.c_str());

    if(!vertexShaderId || !fragmentShaderId) {
        return 0;
    }

    GLCall(unsigned int id = glCreateProgram());
    GLCall(glAttachShader(id, vertexShaderId));
    GLCall(glAttachShader(id, fragmentShaderId));

    GLCall(glLinkProgram(id));
    GLCall(glValidateProgram(id));

    GLCall(glDeleteShader(vertexShaderId));
    GLCall(glDeleteShader(fragmentShaderId));

    return id;
}

unsigned int Shader::CompileShader(GLenum type, const char* src) {
    GLCall(unsigned int id = glCreateShader(type));

    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int success;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
    if(!success) {
        int length;
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
