//
// Created by erikd on 19.10.2024.
//

#pragma once
#include "../Application.h"

class BlockGame: public Application {
public:
    BlockGame();

    void setup() override;
    void update(double dt) override;
    void shutdown() override;
private:
    bool m_vsync = true;
};
