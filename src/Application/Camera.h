//
// Created by erikd on 29.04.2024.
//
#pragma once
#include <glm/glm.hpp>

class Camera {
public:
    void updateMatrix();
    inline glm::mat4& getView() {
        return view;
    }
    inline glm::mat4& getProjection() {
        return projection;
    }
    inline glm::mat4& getVP() {
        return view_projection;
    }
private:
    glm::vec3 pos, rot;

    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 view_projection;
    glm::vec3 mat_pos, mat_rot;
};
