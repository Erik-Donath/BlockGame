//
// Created by erikd on 23.04.2024.
// Refactored by erikd on 27.04.2024.

#pragma once
#include <imgui.h>

struct GLFWwindow;

void ImGUISetup(GLFWwindow* window);
void ImGUIBeforeRender();
void ImGUIAfterRender();
void ImGuiShutdown();
