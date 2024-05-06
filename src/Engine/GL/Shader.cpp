//
// Created by erikd on 30.04.2024.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Shader.h"

using namespace Engine::GL;

static std::string ReadShaderFile(const std::string& path) {
    std::ifstream file(path);
    if(!file.is_open() || !file.good()) {
        std::cerr << "Error: Can't read file '" << path << "'" << std::endl;
        return "";
    }

    std::stringstream ss;
    ss << file.rdbuf();
    file.close();

    return ss.str();
}

Shader::Shader(const std::string &vertex, const std::string &fragment): m_id(0) {
    glid vertexShader = CompileShader(GL_VERTEX_SHADER, ReadShaderFile(vertex).c_str());
    glid fragmentShader = CompileShader(GL_FRAGMENT_SHADER, ReadShaderFile(fragment).c_str());

    if(!vertexShader || !fragmentShader) {
        GLCall(glDeleteShader(vertexShader));
        GLCall(glDeleteShader(fragmentShader));
        m_id = 0;
        return;
    }

    GLCall(m_id = glCreateProgram());
    GLCall(glAttachShader(m_id, vertexShader));
    GLCall(glAttachShader(m_id, fragmentShader));

    GLCall(glLinkProgram(m_id));
    GLCall(glValidateProgram(m_id));

    GLCall(glDeleteShader(vertexShader));
    GLCall(glDeleteShader(fragmentShader));
}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_id));
}

glid Shader::CompileShader(GLenum type, cstr source) {
    GLCall(glid id = glCreateShader(type));

    GLCall(glShaderSource(id, 1, &source, nullptr));
    GLCall(glCompileShader(id));

    int32_t success;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &success));

    if(!success) {
        int32_t length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

        char* msg = new char[length];
        GLCall(glGetShaderInfoLog(id, length, &length, msg));

        std::cerr << "Error: Failed to compile " << GL::GetShaderType(type) << " Shader: " << std::endl << msg << std::endl;
        delete[] msg;

        GLCall(glDeleteShader(id));
        id = 0;
    }
    return id;
}

i32 Shader::GetLocation(const std::string &name) {
    if(m_id == 0)
        return -1;
    if(m_locations.find(name) != m_locations.end())
        return m_locations[name];

    GLCall(i32 location = glGetUniformLocation(m_id, name.c_str()));
    if(location == -1) std::cout << "Warning: Uniform '" << name << "' does not exist" << std::endl;

    m_locations[name] = location;
    return location;
}

void Shader::SetInt(const std::string &name, int32_t v0) {
    Bind();
    GLCall(glUniform1i(GetLocation(name), v0));
}
void Shader::SetFloat(const std::string &name, float v0) {
    Bind();
    GLCall(glUniform1f(GetLocation(name), v0));
}
void Shader::SetVec1(const std::string &name, glm::vec1 v) {
    Bind();
    GLCall(glUniform1fv(GetLocation(name), 1, &v.x));
}
void Shader::SetVec2(const std::string &name, glm::vec2 v) {
    Bind();
    GLCall(glUniform2fv(GetLocation(name), 1, &v.x));
}
void Shader::SetVec3(const std::string &name, glm::vec3 v) {
    Bind();
    GLCall(glUniform3fv(GetLocation(name), 1, &v.x));
}
void Shader::SetMat4(const std::string &name, glm::mat4 m) {
    Bind();
    GLCall(glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, &m[0][0]));
}
void Shader::SetSampler(const std::string& name, int32_t s) {
    Bind();
    GLCall(glUniform1i(GetLocation(name), s));
}
