//
// Created by erikd on 30.04.2024.
//

#pragma once
#include <memory>
#include "Window.h"

namespace Application {
    class Application {
    public:
        void Run();

    protected:
        std::unique_ptr<Window> m_window;
    };
}