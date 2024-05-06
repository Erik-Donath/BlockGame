//
// Created by erikd on 23.04.2024.
// Refactored by erikd on 27.04.2024.

#pragma once
#include <imgui.h>

struct GLFWwindow;

namespace Engine::App {
    class Gui {
    public:
        static void ImGUISetup(GLFWwindow *window);
        static void ImGUIBeforeRender();
        static void ImGUIAfterRender();
        static void ImGuiShutdown();
    };
}