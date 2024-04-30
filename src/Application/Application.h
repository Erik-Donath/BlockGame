//
// Created by erikd on 30.04.2024.
//

#pragma once
#include <memory>
#include "Window.h"

namespace Application {
    class Application {
    public:
        Application();
        ~Application();

        void Run();

        inline GLFWwindow* GetWindowHandle() {
            return m_window->GetHandle();
        }

    protected:
        std::unique_ptr<Window> m_window;
    private:
        static Application* s_instance;
    };
}
