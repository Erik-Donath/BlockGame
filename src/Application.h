//
// Created by erikd on 19.10.2024.
//
#pragma once
#include <string>

#include <glm/glm.hpp>
#include "Window.h"
#include "GUI.h"

class Application {
public:
    Application(const std::string& name, glm::ivec2 size);
    ~Application();

    void run();

    [[nodiscard]] inline int getFPS()    const { return fps;     }
    [[nodiscard]] inline int getAvgFPS() const { return fps_avg; }
    [[nodiscard]] inline int getMinFPS() const { return fps_min; }
    [[nodiscard]] inline int getMaxFPS() const { return fps_max; }
protected:
    virtual void setup();
    virtual void update(double dt);
    virtual void shutdown();

    [[nodiscard]] inline Window* getWindow() const { return m_window; }
    [[nodiscard]] inline GUI* getGUI() const { return m_gui; }
private:
    Window* m_window = nullptr;
    GUI* m_gui = nullptr;

    // FPS Stuff
    int fps = 0, fps_avg = 0, fps_min = 0, fps_max = 0;
};

