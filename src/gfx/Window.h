//
// Created by erikd on 20.04.2024.
//

#pragma once

struct GLFWwindow;

struct Window {
public:
    Window(int w, int h, const char *title, bool resizable = false, int gl_major = 3, int gl_minor = 3, bool gl_core = true);
    ~Window();

    static void PollEvents();
    void SwapBuffers();
    bool ShouldClose();

private:
    GLFWwindow* m_handle = nullptr;
};
