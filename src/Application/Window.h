//
// Created by erikd on 20.04.2024.
// Refactored by erikd on 27.04.2024.

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../Defines.h"


struct WindowProperties {
    const int32_t GLmajor, GLminor;
    const bool GLcore, GLcompat, resizable;

    explicit WindowProperties(bool resizable = false, int32_t major = 3, int32_t minor = 3, bool core = true, bool compat = false) : resizable(resizable), GLcore(core), GLmajor(major), GLminor(minor), GLcompat(compat) { }
};

class Window {

public:
    Window(const char *title, glm::ivec2 size, const WindowProperties& properties);
    ~Window();

    static void PollEvents();
    void SwapBuffers();
    bool ShouldClose();

    void SetFramebufferSizeCallback(GLFWframebuffersizefun func);
    static void SetErrorCallback(GLFWerrorfun func);

    [[nodiscard]] glm::ivec2 GetSize() const;
    [[nodiscard]] int32_t GetWidth() const;
    [[nodiscard]] int32_t GetHeight() const;

    [[nodiscard]] inline GLFWwindow* GetHandle() const {
        return m_handle;
    }

    [[nodiscard]] static Window* GetInstance();

private:
    GLFWwindow* m_handle;

    static Window* s_instance;
};
