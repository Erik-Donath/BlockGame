//
// Created by erikd on 20.04.2024.
// Refactored by erikd on 27.04.2024.

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "../gfx/GL.h"
#include "Window.h"

static Window* window_instance = nullptr;

static void GLFW_DefaultErrorCallback(int error, const char* description_utf8) {
    std::cerr << "Error: GLFW " << error << ": " << description_utf8 << std::endl;
}

static void GLFW_FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    GLCall(glViewport(0, 0, width, height));
}

Window::Window(const char *title, glm::ivec2 size, const WindowProperties& properties) {
    if(window_instance) {
        std::cerr << "Error: The Window class is a singleton." << std::endl;
        return;
    }

    // Setting Default GLFW Callbacks
    glfwSetErrorCallback(GLFW_DefaultErrorCallback);

    // Initialize GLFW
    if(!glfwInit()) {
        m_handle = nullptr;
        std::cerr << "Error: Failed to initialize GLFW" << std::endl;
        return;
    }

    // Settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, properties.GLmajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, properties.GLminor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, properties.GLcore ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, properties.resizable ? GLFW_TRUE : GLFW_FALSE);

    // Create Window
    m_handle = glfwCreateWindow(size.x, size.y, title, nullptr, nullptr);
    if(!m_handle) {
        glfwTerminate();
        std::cerr << "Error: Failed to create Window" << std::endl;
        return;
    }

    // Setting Default Window Callbacks
    glfwSetFramebufferSizeCallback(m_handle, GLFW_FramebufferSizeCallback);

    // Load OpenGL
    glfwMakeContextCurrent(m_handle);
    int glVersion = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if(!glVersion) {
        glfwDestroyWindow(m_handle);
        glfwTerminate();
        std::cerr << "Error: Failed to initialize OpenGL context" << std::endl;
        return;
    }

    // Setting Singleton value & Updating getting Framebuffer Size
    window_instance = this;
    glm::ivec2 frame_size;
    glfwGetFramebufferSize(m_handle, &frame_size.x, &frame_size.y);

    // Clearing Errors, Setting Viewport and Print Open GL Version
    GLClearError();
    GLCall(std::cout << "Info: Loaded OpenGL " << glGetString(GL_VERSION) << std::endl);
    GLCall(glViewport(0, 0, frame_size.x, frame_size.y));

    // Set FSYNC
    glfwSwapInterval(1);
}

Window::~Window() {
    if(window_instance == this) {
        glfwDestroyWindow(m_handle);
        glfwTerminate();
        window_instance = nullptr;
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

[[maybe_unused]] int32_t Window::GetWidth() const {
    glm::ivec2 size = GetSize();
    return size.x;
}

[[maybe_unused]] int Window::GetHeight() const {
    glm::ivec2 size = GetSize();
    return size.y;
}

glm::ivec2 Window::GetSize() const {
    glm::ivec2 size;
    glfwGetWindowSize(m_handle, &size.x, &size.y);
    return size;
}

Window *Window::GetInstance() {
    return window_instance;
}
