//
// Created by erikd on 20.04.2024.
// Refactored by erikd on 27.04.2024.

#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../../Defines.h"

struct WindowProperties {
    bool resizable;
    const bool GLcore;
    const int32_t GLmajor, GLminor;

    WindowProperties() : resizable(false), GLcore(true), GLmajor(3), GLminor(3) { }
};

class Window {
public:
    Window(const char *title, glm::ivec2 size, const WindowProperties& properties);
    ~Window();

    static void PollEvents();
    void SwapBuffers();
    bool ShouldClose();

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
