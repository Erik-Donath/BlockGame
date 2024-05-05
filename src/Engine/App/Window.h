//
// Created by erikd on 30.04.2024.
//
#pragma once
#include <string>

#include "glm/glm.hpp"
#include "../../Defines.h"

struct GLFWwindow;

namespace Engine::App {
    struct WindowOptions {
        const i32 gl_major, gl_minor;
        const bool gl_core, gl_compat;
        const bool m_resizable;

        WindowOptions(i32 major, i32 minor, bool core, bool compat, bool resizable): gl_major(major), gl_minor(minor), gl_core(core), gl_compat(compat), m_resizable(resizable) {}
        static inline WindowOptions Default() { return {3, 3, true, false, true}; }
    };

    class Window {
    public:
        Window(const std::string &title, const glm::ivec2 &size, const WindowOptions &options);
        ~Window();

        [[nodiscard]] glm::ivec2 GetSize() const;
        [[nodiscard]] glm::ivec2 GetFrameSize() const;
        [[nodiscard]] bool ShouldClose() const;
        void SwapBuffers() const;

        static void PollEvents();
        static void SetVSYNC(bool enabled);

        [[nodiscard]] inline GLFWwindow *GetHandle() const {
            return m_handle;
        }
        [[nodiscard]] static inline bool GetVSYNC() {
            return s_vsync;
        }

        static void DefaultErrorCallback(i32 error, cstr description_utf8);
        static void DefaultFramebufferSizeCallback(GLFWwindow *window, i32 width, i32 height);

    protected:
        GLFWwindow *m_handle = nullptr;

        static u32 s_glfwUsed;
        static bool s_vsync;
    };
}