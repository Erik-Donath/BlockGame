//
// Created by erikd on 30.04.2024.
//

#include "Transform.h"
using namespace Scene;

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
