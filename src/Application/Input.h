//
// Created by erikd on 01.05.2024.
//

#pragma once
#include <GLFW/glfw3.h>
#include "Application.h"
#include "../Defines.h"

#define Key(x) GLFW_KEY_#x

namespace Application {
    class Input {
    public:
        inline static i32 GetState(i32 key) {
            return glfwGetKey(Application::GetInstance()->GetWindowHandle(), key);
        }
        inline static bool IsPressed(i32 key) {
            return GetState(key) == GLFW_PRESS;
        }
        inline static bool IsReleased(i32 key) {
            return GetState(key) == GLFW_RELEASE;
        }
    };
}
