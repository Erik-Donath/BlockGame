//
// Created by erikd on 05.05.2024.
//

#include <GLFW/glfw3.h>

#include "Application.h"
#include "Input.h"

using namespace Engine::App;

i32 Input::GetState(i32 key) {
    return glfwGetKey(Application::Application::GetInstance()->GetWindow()->GetHandle(), key);
}

bool Input::IsPressed(i32 key) {
    return GetState(key) == GLFW_PRESS;
}

bool Input::IsReleased(i32 key) {
    return GetState(key) == GLFW_RELEASE;
}
