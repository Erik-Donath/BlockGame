//
// Created by erikd on 12.11.2024.
//

#pragma once
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include "Util.h"

class Window;

class Camera {
public:
    Camera(Window& window, glm::vec3 position, float fov);

    glm::mat4 GetViewMatrix();
    [[nodiscard]] glm::mat4 GetProjectionMatrix() const;

    [[nodiscard]] glm::vec3 GetFront() const;
    [[nodiscard]] glm::vec3 GetRight() const;
    [[nodiscard]] glm::vec3 GetUp() const;

    void update(float deltaTime, bool debug = true);
private:
    void ProcessKeyboardInput(float deltaTime);
    void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
    void RenderImGuiControls();

    Window& m_window;
    bool m_cursorHidden = true;

    glm::vec3 m_position;
    float m_yaw = 0, m_pitch = 0;
    float m_fov = 0, m_aspect = 0;

    float m_speed = 2.5f;
    float m_sensitivity = 0.1f;

    float m_near = 0.1f, m_far = 100.0f;
};
