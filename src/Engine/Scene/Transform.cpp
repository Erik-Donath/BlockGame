//
// Created by erikd on 30.04.2024.
//

#include "Transform.h"
using namespace Engine::Scene;

glm::mat4 WorldTransform::GetModelMatrix() {
    if(m_updateMatrix) {
        glm::mat4 translate = glm::translate(glm::mat4(1.0), m_position);
        //glm::mat4 rotate = glm::rotate(glm::mat4(1.0), m_direction);
        glm::mat4 scale = glm::scale(glm::mat4(1.0), m_scale);

        //m_modelMatrix = translate * rotate * scale;
        m_modelMatrix = translate * scale;
        m_updateMatrix = false;
    }

    return m_modelMatrix;
}
