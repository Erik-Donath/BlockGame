//
// Created by erikd on 19.10.2024.
//

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GL.h"
#include "Window.h"

static void DefaultErrorCallback(int32_t error, const char* description_utf8) {
    std::cerr << "Error: GLFW " << error << ": " << description_utf8 << std::endl;
}
static void DefaultFramebufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height) {
    GLCall(glViewport(0, 0, width, height));
}

Window::Window(const std::string& titel, glm::ivec2 size): m_handle(nullptr) {
    glfwSetErrorCallback(DefaultErrorCallback);
    int err = glfwInit();
    if(!err) {
        std::cerr << "Error(" << err << "): Failed to initialize GLFW" << std::endl;
        std::exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_handle = glfwCreateWindow(size.x, size.y, titel.c_str(), nullptr, nullptr);
    if(!m_handle) {
        std::cerr << "Error: Failed to create Window" << std::endl;
        std::exit(1);
    }

    glfwMakeContextCurrent(m_handle);
    int glVersion = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if(!glVersion) {
        std::cerr << "Error: Failed to initialize OpenGL context" << std::endl;
        std::exit(1);
    }

    glfwSetFramebufferSizeCallback(m_handle, DefaultFramebufferSizeCallback);

    glm::ivec2 frame_size = GetFrammbufferSize();
    GLCall(glViewport(0, 0, frame_size.x, frame_size.y));
}
Window::~Window() {
    if(m_handle) glfwDestroyWindow(m_handle);
    glfwTerminate();
}

void Window::SwapBuffers() const {
    glfwSwapBuffers(m_handle);
}
void Window::PollEvents() {
    glfwPollEvents();
}
bool Window::Opened() {
    return !glfwWindowShouldClose(m_handle);
}

void Window::Close() const {
    glfwSetWindowShouldClose(m_handle, GLFW_TRUE);
}

glm::ivec2 Window::GetWindowSize() {
    glm::ivec2 size;
    glfwGetWindowSize(m_handle, &size.x, &size.y);
    return size;
}
glm::ivec2 Window::GetFrammbufferSize() {
    glm::ivec2 size;
    glfwGetFramebufferSize(m_handle, &size.x, &size.y);
    return size;
}

float Window::GetAspectRatio() {
    glm::ivec2 size = GetFrammbufferSize();
    return static_cast<float>(size.x) / static_cast<float>(size.y);
}

void Window::SwapInterval(int vsync) {
    glfwSwapInterval(vsync);
}
