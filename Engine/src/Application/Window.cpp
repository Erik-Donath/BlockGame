//
// Created by erikd on 05.08.2024.
//

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <CustomException.h>
#include <Application/Window.h>

using namespace Engine::Application;
u32 Window::s_glfwUsed = 0;

Window::Window(str title, WindowProperties prop): m_handle(nullptr) {
    // Init GLFW & Set Window Prop's
    if(!initGLFW()) throw CustomException("Failed to initialize GLFW");
    SetProperties(prop);

    // Create Window
    m_handle = glfwCreateWindow(prop.sizeX, prop.sizeY, title, nullptr, nullptr);
    if(!m_handle) {
        throw CustomException("Failed to create Window");
    }

    // Set Window Callbacks
    glfwSetFramebufferSizeCallback(m_handle, Window::GLFWFramebufferSizeCallback);

    // Create OpenGL Context
    glfwMakeContextCurrent(m_handle);
    int glVersion = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if(!glVersion) {
        throw CustomException("Error: Failed to initialize OpenGL context with GLAS loader");
    }
}

Window::~Window() {
    close();
    terminateGLFW();
}

void Window::close() {
    glfwDestroyWindow(m_handle);
    m_handle = nullptr;
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(m_handle);
}

bool Window::initGLFW() {
    if(s_glfwUsed == 0) {
        // Set GLFW Callbacks
        glfwSetErrorCallback(Window::GLFWErrorCallback);

        // Init GLFW
        if(!glfwInit()) {
            return false;
        }
        Log("Info: Initialized GLFW");
    }

    s_glfwUsed += 1;
    return true;
}

void Window::terminateGLFW() {
    s_glfwUsed -= 1;
    if(s_glfwUsed == 0) {
        glfwTerminate();
        Log("Info: Terminated GLFW");
    }
}

void Window::SetProperties(WindowProperties prop) {
    OpenGLInfo glInfo = prop.glInfo;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glInfo.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glInfo.minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, glInfo.core ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, glInfo.compat ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, prop.resizable ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
}

void Window::SwapBuffers() const {
    glfwSwapBuffers(m_handle);
}

void Window::PollEvents() {
    glfwPollEvents();
}

void Window::GLFWErrorCallback(i32 error, str description_utf8) {
    Err("Error: GLFW " << error << ": " << description_utf8);
}

#define GLCall(x) x
void Window::GLFWFramebufferSizeCallback(GLFWwindow* window, i32 width, i32 height) {
    GLCall(glViewport(0, 0, width, height));
}
