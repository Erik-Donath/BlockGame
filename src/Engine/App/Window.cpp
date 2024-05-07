//
// Created by erikd on 30.04.2024.
//

#include <iostream>
#include "../GL/GL.h"
#include "Window.h"

using namespace Engine::App;

u32 Window::s_windowCount = 0;
bool Window::s_currentSwapInterval = false;

void Window::DefaultErrorCallback(i32 error, cstr description_utf8) {
    std::cerr << "Error: GLFW " << error << ": " << description_utf8 << std::endl;
}
void Window::DefaultFramebufferSizeCallback(GLFWwindow* window, i32 width, i32 height) {
    GLCall(glViewport(0, 0, width, height));
}

Window::Window(const std::string &title, const glm::ivec2 &size, const WindowProperties &properties) {
    if(!s_windowCount) {
        SetErrorCallback(Window::DefaultErrorCallback);
        if(!glfwInit()) {
            std::cerr << "Error: Failed to initialize GLFW" << std::endl;
            m_handle = nullptr;
            return;
        }
    }
    s_windowCount += 1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, properties.GLMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, properties.GLMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, properties.GLCore ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, properties.GLCompat ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, properties.resizable ? GLFW_TRUE : GLFW_FALSE);

    m_handle = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
    if(!m_handle) {
        std::cerr << "Error: Failed to create Window" << std::endl;
        return;
    }

    // Default Callbacks
    SetFramebufferSizeCallback(Window::DefaultFramebufferSizeCallback);

    glfwMakeContextCurrent(m_handle);
    int glVersion = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if(!glVersion) {
        std::cerr << "Error: Failed to initialize OpenGL context" << std::endl;
        glfwDestroyWindow(m_handle);
        return;
    }

    // Clearing Errors, Setting Viewport and Print Open GL Version
    GLClearError();
    glm::ivec2 frame_size = GetFrameSize();
    GLCall(std::cout << "Info: Loaded OpenGL " << glGetString(GL_VERSION) << std::endl);
    GLCall(glViewport(0, 0, frame_size.x, frame_size.y));

    // Set FSYNC
    SetVSYNC(true);
}

Window::~Window() {
    glfwDestroyWindow(m_handle);

    s_windowCount -= 1;
    if(!s_windowCount) {
        glfwTerminate();
    }
}

void Window::SwapBuffers() const {
    glfwSwapBuffers(m_handle);
}
void Window::PollEvents() {
    glfwPollEvents();
}
[[nodiscard]] bool Window::ShouldClose() const {
    return glfwWindowShouldClose(m_handle);
}

void Window::SetVSYNC(bool enable) {
    s_currentSwapInterval = enable;
    glfwSwapInterval(enable ? GLFW_TRUE : GLFW_FALSE);
}

glm::ivec2 Window::GetSize() const {
    glm::ivec2 size;
    glfwGetWindowSize(m_handle, &size.x, &size.y);
    return size;
}

glm::ivec2 Window::GetFrameSize() const {
    glm::ivec2 size;
    glfwGetFramebufferSize(m_handle, &size.x, &size.y);
    return size;
}
