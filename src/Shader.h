//
// Created by erikd on 12.11.2024.
//

#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include "glm/glm.hpp"
#include "GL.h"

enum ShaderType: GLenum {
    None = GL_NONE,
    VertexShader = GL_VERTEX_SHADER,
    FragmentShader = GL_FRAGMENT_SHADER,
};

struct Shader {
public:
    Shader(const std::string& file, ShaderType type);
    ~Shader();

    [[nodiscard]] inline glid getID() const {
        return m_id;
    }
    [[nodiscard]] inline ShaderType getType() const {
        return m_type;
    }
    [[nodiscard]] inline std::string getFile() const {
        return m_file;
    }
private:
    std::string readFile();

    ShaderType m_type;
    glid m_id;
    std::string m_file;
};

class ShaderProgram {
public:
    explicit ShaderProgram(const std::vector<std::shared_ptr<Shader>>& shaders);
    ~ShaderProgram();

    void bind() const;
    static void unbind();

    void setUniformMat4(const std::string& name, const glm::mat4& matrix);
    GLint getUniformLocation(const std::string& name);

    inline void use() const { bind(); }
    [[nodiscard]] inline glid getID() const {
        return m_id;
    }
private:
    glid m_id;
    std::unordered_map<std::string, GLint> m_uniformLocationCache;
};

