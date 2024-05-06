//
// Created by erikd on 30.04.2024.
//
#pragma once
#include <string>
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "../../Defines.h"

namespace Engine::App {
    struct WindowProperties {
        const i32 GLmajor, GLminor;
        const bool GLcore, GLcompat, resizable;

        explicit WindowProperties(bool resizable, i32 major, i32 minor, bool core, bool compat)
        : resizable(resizable), GLcore(core), GLmajor(major), GLminor(minor), GLcompat(compat) { }

        static inline WindowProperties Default() {
            return WindowProperties(true, 3, 3, true, false);
        }
    };

    class Window {
    public:
        Window(const std::string &title, const glm::ivec2 &size, const WindowProperties &properties);
        ~Window();

        [[nodiscard]] inline GLFWwindow *GetHandle() const {
            return m_handle;
        }

        [[nodiscard]] glm::ivec2 GetSize() const;
        [[nodiscard]] glm::ivec2 GetFrameSize() const;

        [[nodiscard]] inline bool ShouldClose() const {
            return glfwWindowShouldClose(m_handle);
        }
        inline void SwapBuffers() const {
            glfwSwapBuffers(m_handle);
        }

        inline static void SetVSYNC(bool enable) {
            s_currentSwapInterval = enable;
            glfwSwapInterval(enable ? GLFW_TRUE : GLFW_FALSE);
        }
        inline static bool GetVSYNC() {
            return s_currentSwapInterval;
        }
        inline static void PollEvents() {
            glfwPollEvents();
        }

        inline static void SetErrorCallback(const GLFWerrorfun &callback) {
            glfwSetErrorCallback(callback);
        }
        inline void SetFramebufferSizeCallback(const GLFWframebuffersizefun &callback) const {
            glfwSetFramebufferSizeCallback(m_handle, callback);
        }
        inline void SetKeyCallback(const GLFWkeyfun &callback) {
            glfwSetKeyCallback(m_handle, callback);
        }

        static void DefaultErrorCallback(i32 error, cstr description_utf8);
        static void DefaultFramebufferSizeCallback(GLFWwindow *window, i32 width, i32 height);

    protected:
        GLFWwindow *m_handle;

        static u32 s_windowCount;
        static bool s_currentSwapInterval;
    };
}