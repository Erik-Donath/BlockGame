//
// Created by erikd on 30.04.2024.
//

#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#define ForwardVector  glm::vec3( 0.0f,  0.0f,  1.0f)
#define BackwardVector glm::vec3( 0.0f,  0.0f, -1.0f)
#define UpVector       glm::vec3( 0.0f,  1.0f,  0.0f)
#define DownVector     glm::vec3( 0.0f, -1.0f,  0.0f)
#define RightVector    glm::vec3( 1.0f,  0.0f,  0.0f)
#define LeftVector     glm::vec3(-1.0f,  0.0f,  0.0f)

namespace Scene {
    struct SimpleTransform {
    public:
        SimpleTransform() : m_position(0.0, 0.0, 0.0), m_rotation(0.0, 0.0, 0.0, 1.0), m_recalculate(true) { }

        inline void SetPosition(const glm::vec3& position) {
            m_position = position;
            m_recalculate = true;
        }
        inline void SetRotation(const glm::quat& rotation) {
            m_rotation = rotation;
            m_recalculate = true;
        }
        inline void SetRotationEuler(const glm::vec3& angles) {
            m_rotation = glm::quat(angles);
            m_recalculate = true;
        }
        inline void SetValues(const glm::vec3& position, const glm::quat& rotation) {
            m_position = position;
            m_rotation = rotation;
            m_recalculate = true;
        }

        [[nodiscard]] inline glm::vec3 GetPosition() const {
            return m_position;
        }
        [[nodiscard]] inline glm::quat GetRotation() const {
            return m_rotation;
        }
        [[nodiscard]] inline glm::vec3 GetRotationEuler() const {
            return eulerAngles(m_rotation);
        }

        inline friend bool operator==(const SimpleTransform& first, const SimpleTransform& second) {
            return first.m_position == second.m_position && first.m_rotation == second.m_rotation;
        }
        inline friend bool operator!=(const SimpleTransform& first, const SimpleTransform& second) {
            return !(first == second);
        }
    protected:
        glm::vec3 m_position;
        glm::quat m_rotation;
        bool m_recalculate; // Is only used in Object Transform at the moment
    };

    struct ObjectTransform : public SimpleTransform {
    public:
        ObjectTransform(): SimpleTransform(), m_scale(1.0, 1.0, 1.0), m_modelMatrix(1.0) { }

        inline void SetScale(const glm::vec3& scale) {
            m_scale = scale;
            m_recalculate = true;
        }

        [[nodiscard]] inline glm::vec3 GetScale() const {
            return m_scale;
        }
        [[nodiscard]] glm::mat4 GetModelMatrix();

        inline friend bool operator==(const ObjectTransform& first, const ObjectTransform& second) {
            return first.m_position == second.m_position && first.m_rotation == second.m_rotation && first.m_scale == second.m_scale;
        }
        inline friend bool operator!=(const ObjectTransform& first, const ObjectTransform& second) {
            return !(first == second);
        }
    private:
        glm::vec3 m_scale;
        glm::mat4 m_modelMatrix;
    };
}
