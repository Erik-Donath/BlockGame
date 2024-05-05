//
// Created by erikd on 01.05.2024.
//

#pragma once
#include "../../Defines.h"

// TEMPORARILY!
#include <GLFW/glfw3.h>

#define Key(s) GLFW_KEY_ ## s

namespace Engine::App {
    class Input {
    public:
        static i32 GetState(i32 key);
        static bool IsPressed(i32 key);
        static bool IsReleased(i32 key);
    };
}
