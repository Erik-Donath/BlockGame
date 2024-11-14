//
// Created by erikd on 19.10.2024.
//

#pragma once
#include "imgui.h"
#include "Window.h"

class GUI {
public:
    explicit GUI(Window& window);
    ~GUI();

    static void Before();
    static void After();
};
