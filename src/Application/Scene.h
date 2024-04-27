//
// Created by erikd on 27.04.2024.
//
#pragma once

class Renderer;
class Window;

class Scene {
public:
    virtual void Init(const Window& window);
    virtual void Shutdown();

    virtual void Update();
    virtual void Render(const Renderer& renderer);
};
