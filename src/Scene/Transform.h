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
        inline void SetPosition(const glm::vec3& position) {
            m_position = position;
            m_changed = true;
        }
        inline void SetRotation(const glm::quat& rotation) {
            m_rotation = rotation;
            m_changed = true;
        }
        inline void SetRotationEuler(const glm::vec3& angles) {
            m_rotation = glm::quat(angles);
            m_changed = true;
        }
        inline void SetValues(const glm::vec3& position, const glm::quat& rotation) {
            m_position = position;
            m_rotation = rotation;
            m_changed = true;
        }
        inline void HandledChange() {
            m_changed = false;
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
        [[nodiscard]] inline bool didValuesChange() const {
            return m_changed;
        }
    protected:
        glm::vec3 m_position;
        glm::quat m_rotation;
        bool m_changed = true;
    };

    struct ObjectTransform : public SimpleTransform {
    public:
        inline void SetScale(const glm::vec3& scale) {
            m_scale = scale;
            m_changed = true;
        }

        [[nodiscard]] inline glm::vec3 GetScale() const {
            return m_scale;
        }
        [[nodiscard]] glm::mat4 GetModelMatrix();
    private:
        glm::vec3 m_scale;
        glm::mat4 m_modelMatrix;
    };
}
