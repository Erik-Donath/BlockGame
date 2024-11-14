//
// Created by erikd on 19.10.2024.
//
#pragma once

#include <cstdint>
#include <string>
#include <glm/glm.hpp>

struct GLFWwindow;

class Window {
public:
    Window(const std::string& title, glm::ivec2 size);
    ~Window();

    static void SwapInterval(int vsync);
    void SwapBuffers() const;
    static void PollEvents();
    bool Opened();

    void Close() const;
    glm::ivec2 GetWindowSize();
    glm::ivec2 GetFrammbufferSize();
    float GetAspectRatio();

    [[nodiscard]] inline GLFWwindow* GetHandle() const {
        return m_handle;
    }
private:
    GLFWwindow* m_handle;
};
