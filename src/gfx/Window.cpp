//
// Created by erikd on 20.04.2024.
//

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GL.h"
#include "Window.h"

static void GLFW_DefaultErrorCallback(int error, const char* description_utf8) {
    std::cerr << "Error: GLFW " << error << ": " << description_utf8 << std::endl;
}

static bool windowCreated = false;
Window::Window(int w, int h, const char *title, bool resizable, int gl_major, int gl_minor, bool gl_core): m_handle(nullptr) {
    if(windowCreated) {
        std::cerr << "Error: The Window class is a singleton." << std::endl;
        return;
    }
    windowCreated = true;

    // Setting Default Callbacks
    glfwSetErrorCallback(GLFW_DefaultErrorCallback);

    // Initialize GLFW
    if(!glfwInit()) {
        m_handle = nullptr;
        std::cerr << "Error: Failed to initialize GLFW" << std::endl;
        return;
    }

    // Settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, gl_core ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);

    // Create Window
    m_handle = glfwCreateWindow(w, h, title, nullptr, nullptr);
    if(!m_handle) {
        m_handle = nullptr;
        glfwTerminate();
        std::cerr << "Error: Failed to create Window" << std::endl;
        return;
    }

    // Load OpenGL
    glfwMakeContextCurrent(m_handle);
    int glVersion = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if(!glVersion) {
        glfwTerminate();
        std::cerr << "Error: Failed to initialize OpenGL context" << std::endl;
        return;
    }

    // Clearing Errors, Setting Viewport and Print Open GL Version
    GLClearError();
    GLCall(std::cout << "Info: Loaded OpenGL " << glGetString(GL_VERSION) << std::endl);
    GLCall(glViewport(0, 0, w, h));
}

Window::~Window() {
    if(windowCreated) {
        glfwDestroyWindow(m_handle);
        glfwTerminate();
        windowCreated = false;
    }
}

void Window::PollEvents() {
    glfwPollEvents();
}

void Window::SwapBuffers() {
    glfwSwapBuffers(m_handle);
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(m_handle);
}
