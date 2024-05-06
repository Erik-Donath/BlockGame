//
// Created by erikd on 04.05.2024.
//

#include "../Rendering/GL.h"
#include "../Application/Application.h"
#include "Camera.h"

void Scene::Camera::Update(double deltaTime) {
    double time = Application::Application::GetTime();
    m_transform.SetPosition(glm::vec3(cos(time), 0.0f, sin(time)));

    glm::ivec2 frameBufferSize = Application::Application::GetInstance()->GetWindow()->GetFrameSize();
    if(frameBufferSize != m_pm_frameSize) RecalculateProjectionMatrix(frameBufferSize);
    if(m_transform != m_vm_transform) RecalculateViewMatrix(m_transform);
    if(m_recalculate_vp) RecalculateVPMatrix();
}

void Scene::Camera::RecalculateProjectionMatrix(glm::ivec2& frameBufferSize) {
    m_aspectRatio = frameBufferSize.x == 0 || frameBufferSize.y == 0 ? 0 : (float)frameBufferSize.x / (float)frameBufferSize.y;
    m_projectionMatrix = glm::perspective(m_fov, m_aspectRatio, m_nearPlan, m_farPlan);

    m_pm_frameSize = frameBufferSize;
    m_recalculate_vp = true;
}

void Scene::Camera::RecalculateViewMatrix(::Scene::SimpleTransform &transform) {
    glm::vec3 lookDirection = ForwardVector * transform.GetRotation();
    m_viewMatrix = glm::lookAt(transform.GetPosition(), transform.GetPosition() + lookDirection, UpVector);

    m_vm_transform = transform;
    m_recalculate_vp = true;
}

void Scene::Camera::RecalculateVPMatrix() {
    m_vpMatrix = m_projectionMatrix * m_viewMatrix;
    m_recalculate_vp = false;
}
