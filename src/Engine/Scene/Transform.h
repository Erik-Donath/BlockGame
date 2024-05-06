//
// Created by erikd on 30.04.2024.
//

#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"

#define ForwardVector  glm::vec3( 0.0f,  0.0f,  1.0f)
#define BackwardVector glm::vec3( 0.0f,  0.0f, -1.0f)
#define UpVector       glm::vec3( 0.0f,  1.0f,  0.0f)
#define DownVector     glm::vec3( 0.0f, -1.0f,  0.0f)
#define RightVector    glm::vec3( 1.0f,  0.0f,  0.0f)
#define LeftVector     glm::vec3(-1.0f,  0.0f,  0.0f)

namespace Engine::Scene {
    struct WorldTransform {
    public:
        glm::mat4 GetModelMatrix();

        inline void SetPosition(const glm::vec3& pos) {
            m_position = pos;
            m_updateMatrix = true;
        }
        inline void SetScale(const glm::vec3& scale) {
            m_scale = scale;
            m_updateMatrix = true;
        }
        inline void SetDirection(const glm::vec3& dir) {
            m_direction = dir;
            m_updateMatrix = true;
        }

        [[nodiscard]] inline glm::vec3 GetPosition() const {
            return m_position;
        }
        [[nodiscard]] inline glm::vec3 GetScale() const {
            return m_scale;
        }
        [[nodiscard]] inline glm::vec3 GetDirection() const {
            return m_direction;
        }

        inline friend bool operator==(const WorldTransform& lhs, const WorldTransform& rhs) {
            return (
                    lhs.m_position == rhs.m_position &&
                    lhs.m_scale == rhs.m_scale &&
                    lhs.m_direction == rhs.m_direction
            );
        }
        inline friend bool operator!=(const WorldTransform& lhs, const WorldTransform& rhs) {
            return !(lhs == rhs);
        }
    private:
        glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 m_direction = glm::vec3(1.0f, 0.0f, 0.0f);

        bool m_updateMatrix = true;
        glm::mat4 m_modelMatrix;
    };
}
