//
// Created by erikd on 30.04.2024.
//
#pragma once
#include <glm/glm.hpp>

#include "VertexArray.h"
#include "Shader.h"

#define DefaultClearColor glm::vec4(0.2f, 0.3f, 0.3f, 1.0f)

namespace Engine::GL {
    enum RenderMode: GLenum {
        Point = GL_POINT,
        Line = GL_LINE,
        Fill = GL_FILL
    };

    class Renderer {
    public:
        inline static void Clear() {
            GLCall(glClear(GL_COLOR_BUFFER_BIT));
        }
        inline static void ClearColor(glm::vec4 color) {
            GLCall(glClearColor(color.r, color.g, color.b, color.a));
        }
        inline static void Draw(const VertexArray& vao, const IndexBuffer& ebo, const Shader& shader) {
            vao.Bind();
            ebo.Bind();
            shader.Bind();
            GLCall(glDrawElements(GL_TRIANGLES, ebo.GetCount(), ebo.GetType(), nullptr));
        }
        inline static void SetBlendFunction(GLenum src, GLenum dst, GLenum func) {
            GLCall(glBlendFunc(src, dst));
            GLCall(glBlendEquation(func));
        }
        inline static void EnableBlending() {
            GLCall(glEnable(GL_BLEND));
        }
        inline static void DisableBlending() {
            GLCall(glDisable(GL_BLEND));
        }
        inline static void SetMode(RenderMode mode) {
            GLCall(glPointSize(10.0f));
            GLCall(glLineWidth(10.0f));
            GLCall(glPolygonMode(GL_FRONT_AND_BACK, mode));
        }
    };
}
