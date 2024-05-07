//
// Created by erikd on 04.05.2024.
//

#include "../GL/GL.h"
#include "../App/Application.h"
#include "Camera.h"

using namespace Engine::Scene;

void Camera::Update(double deltaTime) {
    double time = Engine::App::Application::GetTime();
    m_transform.SetPosition(glm::vec3(cos(time), 0.0f, -1.5f));
    //m_transform.SetPosition(glm::vec3(0.0f, 0.0f, -1.5f));

    glm::ivec2 frameBufferSize = Engine::App::Application::GetInstance()->GetWindow()->GetFrameSize();
    if(frameBufferSize != m_pm_frameSize) RecalculateProjectionMatrix(frameBufferSize);
    if(m_transform != m_vm_transform) RecalculateViewMatrix(m_transform);
    if(m_recalculate_vp) RecalculateVPMatrix();
}

void Camera::RecalculateProjectionMatrix(glm::ivec2& frameBufferSize) {
    m_aspectRatio = frameBufferSize.x == 0 || frameBufferSize.y == 0 ? 0 : (float)frameBufferSize.x / (float)frameBufferSize.y;
    m_projectionMatrix = glm::perspective(m_fov, m_aspectRatio, m_nearPlan, m_farPlan);

    m_pm_frameSize = frameBufferSize;
    m_recalculate_vp = true;
}

void Camera::RecalculateViewMatrix(Engine::Scene::SimpleTransform &transform) {
    glm::vec3 lookDirection = ForwardVector * transform.GetRotation();
    m_viewMatrix = glm::lookAt(transform.GetPosition(), transform.GetPosition() + lookDirection, UpVector);

    m_vm_transform = transform;
    m_recalculate_vp = true;
}

void Camera::RecalculateVPMatrix() {
    m_vpMatrix = m_projectionMatrix * m_viewMatrix;
    m_recalculate_vp = false;
}
