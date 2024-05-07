//
// Created by erikd on 30.04.2024.
//

#include "Transform.h"
using namespace Engine::Scene;

glm::mat4 ObjectTransform::GetModelMatrix() {
    if(m_recalculate) {
        glm::mat4 translate = glm::translate(glm::mat4(1.0), m_position);
        glm::mat4 rotate = glm::mat4_cast(m_rotation);
        glm::mat4 scale = glm::scale(glm::mat4(1.0), m_scale);

        m_modelMatrix = translate * rotate * scale;
        m_recalculate = false;
    }

    return m_modelMatrix;
}

glm::mat4 WorldTransform::getModelMatrix() {
    if(m_changedValues) {
        glm::rotate(glm::mat4(1.0f), 1.0f, glm::vec3(1.0f));
        m_changedValues = false;
    }
    return m_modelMatrix;
}
