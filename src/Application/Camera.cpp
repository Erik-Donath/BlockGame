//
// Created by erikd on 29.04.2024.
//

#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

void Camera::updateMatrix() {
    if(pos != mat_pos || rot != mat_rot) {
        view = glm::lookAt(pos, pos + rot, glm::vec3(0.0f, 1.0f, 0.0f));

        float asp
        projection = glm::perspective(glm::half_pi<float>(), aspectRatio, 0.1f, 1000f);
    }
}
