//
// Created by erikd on 12.11.2024.
//

#include "../GUI.h"
#include "GLFW/glfw3.h"
#include "Camera.h"

Camera::Camera(Window& window, glm::vec3 position, float fov): m_window(window), m_position(position), m_fov(fov) {
    glfwSetInputMode(window.GetHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(m_position, m_position + GetFront(), WorldUp);
}

glm::mat4 Camera::GetProjectionMatrix() const {
    return glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
}

glm::vec3 Camera::GetFront() const {
    glm::vec3 front = glm::normalize(glm::vec3(
        cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)),
        sin(glm::radians(m_pitch)),
        sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch))
    ));
    return front;
}

glm::vec3 Camera::GetRight() const {
    return glm::normalize(glm::cross(GetFront(), WorldUp));
}

glm::vec3 Camera::GetUp() const {
    return glm::normalize(glm::cross(GetRight(), GetFront()));
}

void Camera::update(float deltaTime, bool debug) {
    m_aspect = m_window.GetAspectRatio();
    ProcessKeyboardInput(deltaTime);

    double xpos, ypos;
    glfwGetCursorPos(m_window.GetHandle(), &xpos, &ypos);

    static double lastX = xpos;
    static double lastY = ypos;

    double xOffset = xpos - lastX;
    double yOffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    ProcessMouseMovement((float)xOffset, (float)yOffset);
    if(debug) RenderImGuiControls();
}


void Camera::ProcessKeyboardInput(float deltaTime) {
    GLFWwindow* window = m_window.GetHandle();
    glm::vec3 front = GetFront();
    glm::vec3 right = GetRight();

    float velocity = m_speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_position += front * velocity;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_position -= front * velocity;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_position -= right * velocity;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_position += right * velocity;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_position += WorldUp * velocity;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        m_position -= WorldUp * velocity;

    static bool changed_key = false;
    bool now = glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS;
    if(!changed_key && now) {
        m_cursorHidden = !m_cursorHidden;
        glfwSetInputMode(window, GLFW_CURSOR, m_cursorHidden ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
    }
    changed_key = now;
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
    xOffset *= m_sensitivity;
    yOffset *= m_sensitivity;

    m_yaw += xOffset;
    m_pitch += yOffset;

    if (constrainPitch) {
        if (m_pitch > 90.0f)  m_pitch = 90.0f;
        if (m_pitch < -90.0f) m_pitch = -90.0f;
    }
}

void Camera::RenderImGuiControls() {
    ImGui::Begin("Camera Controls");
    ImGui::SliderFloat3("Position", &m_position.x, -10.0f, 10.0f);
    ImGui::SliderFloat("Yaw", &m_yaw, -180.0f, 180.0f);
    ImGui::SliderFloat("Pitch", &m_pitch, -90.0f, 90.0f);
    ImGui::Spacing();
    ImGui::SliderFloat("FOV", &m_fov, -90.0f, 90.0f);
    ImGui::SliderFloat("Speed", &m_speed, 0.0f, 10.0f);
    ImGui::SliderFloat("Sensitivity", &m_sensitivity, 0.1f, 2.0f);
    ImGui::Spacing();
    ImGui::SliderFloat("Near Plane", &m_near, 0.01f, 100.0f);
    ImGui::SliderFloat("Far Plane", &m_far, 0.01f, 100.0f);
    ImGui::End();
}
