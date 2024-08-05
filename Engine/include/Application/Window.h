//
// Created by erikd on 05.08.2024.
//

#pragma once
#include "Define.h"

struct GLFWwindow;

namespace Engine::Application {
    struct OpenGLInfo {
    public:
        const i32 major, minor;
        const bool core, compat;

        static inline OpenGLInfo Default() {
            return {3, 3, true, false };
        }
    };

    struct WindowProperties {
    public:
        OpenGLInfo glInfo;
        i32 sizeX, sizeY;
        bool resizable;

        static inline WindowProperties Default() {
            return { OpenGLInfo::Default(), 1920, 1080, true };
        }
    };

    class Window {
    public:
        Window(str title, WindowProperties properties);
        ~Window();
        void close();

        void SwapBuffers() const;
        [[nodiscard]] bool ShouldClose();

        static void PollEvents();

        static void GLFWErrorCallback(i32 error, str description_utf8);
        static void GLFWFramebufferSizeCallback(GLFWwindow* window, i32 width, i32 height);
    private:
        GLFWwindow* m_handle;

        static u32 s_glfwUsed;
        static bool initGLFW();
        static void terminateGLFW();
        static void SetProperties(WindowProperties properties);
    };

}
