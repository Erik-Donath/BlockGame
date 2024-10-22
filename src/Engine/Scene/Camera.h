//
// Created by erikd on 04.05.2024.
//
#pragma once

#include "glm/glm.hpp"
#include "../App/Window.h"
#include "Transform.h"

namespace Engine::Scene {
    class Camera {
    public:
        Camera() {
            m_transform.SetPosition({0.0f, 0.0f, 3.0f});
        }

        void Update(double deltaTime);

        void RecalculateProjectionMatrix(glm::ivec2& frameBufferSize);
        void RecalculateViewMatrix(Engine::Scene::SimpleTransform& transform);
        void RecalculateVPMatrix();

        [[nodiscard]] inline glm::mat4 GetProjectionMatrix() const {
            return m_projectionMatrix;
        }
        [[nodiscard]] inline glm::mat4 GetViewMatrix() const {
            return m_viewMatrix;
        }
        [[nodiscard]] inline glm::mat4 GetVPMatrix() const {
            return m_vpMatrix;
        }
    private:
        Engine::Scene::SimpleTransform m_transform;

        float m_nearPlan = 0.1, m_farPlan = 100, m_fov = glm::radians(45.0f);
        float m_aspectRatio = 0;

        glm::ivec2 m_pm_frameSize = {0, 0 };
        Engine::Scene::SimpleTransform m_vm_transform;
        bool m_recalculate_vp = true;

        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewMatrix;
        glm::mat4 m_vpMatrix;
    };
}
