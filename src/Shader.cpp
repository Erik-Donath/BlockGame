//
// Created by erikd on 12.11.2024.
//

#include <fstream>
#include <sstream>
#include <iostream>

#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"

Shader::Shader(const std::string& file, ShaderType type): m_file(file), m_type(type), m_id(0) {
    std::string source = readFile();
    const char* src = source.c_str();

    GLCall(glid shader = glCreateShader(type));
    GLCall(glShaderSource(shader, 1, &src, nullptr));
    GLCall(glCompileShader(shader));

    int success;
    GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if (!success) {
        char infoLog[512];
        GLCall(glGetShaderInfoLog(shader, 512, nullptr, infoLog));
        std::cerr << file << ":0: Shader Compilation Error:\n" << infoLog << std::endl;

        GLCall(glDeleteShader(shader));
        m_id = 0;
        return;
    }

    m_id = shader;
    std::cout << "Created Shader<" << m_id << "> as " << type << " from source '" << file << "'" << std::endl;
}

Shader::~Shader() {
    if(m_id) {
        GLCall(glDeleteShader(m_id));
        std::cout << "Deleted Shader<" << m_id << ">" << std::endl;
    }
}

std::string Shader::readFile() {
    std::ifstream file(m_file);
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

ShaderProgram::ShaderProgram(const std::vector<std::shared_ptr<Shader>>& shaders): m_id(0) {
    GLCall(glid shaderProgram = glCreateProgram());

    for(const auto& shader: shaders) {
        if(!shader->getID()) {
            GLCall(glDeleteProgram(shaderProgram));
            m_id = 0;
            return;
        }
        GLCall(glAttachShader(shaderProgram, shader->getID()));
    }

    GLCall(glLinkProgram(shaderProgram));
    for(const auto& shader: shaders) {
        GLCall(glDetachShader(shaderProgram, shader->getID()));
    }

    m_id = shaderProgram;
    std::cout << "Created Program<" << m_id << ">" << std::endl;
}

ShaderProgram::~ShaderProgram() {
    if(m_id) {
        GLCall(glDeleteProgram(m_id));
        std::cout << "Deleted Program<" << m_id << ">" << std::endl;
    }
}

void ShaderProgram::bind() const {
    GLCall(glUseProgram(m_id));
}

void ShaderProgram::unbind() {
    GLCall(glUseProgram(0));
}

void ShaderProgram::setUniformMat4(const std::string& name, const glm::mat4& matrix) {
    GLint location = getUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

GLint ShaderProgram::getUniformLocation(const std::string &name) {
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) {
        return m_uniformLocationCache[name];
    }

    // Ansonsten glGetUniformLocation verwenden und Location in den Cache speichern
    GLCall(GLint location = glGetUniformLocation(m_id, name.c_str()));
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' doesn't exist or is not used in shader.\n";
    }
    m_uniformLocationCache[name] = location;
    return location;
}
