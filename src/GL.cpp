//
// Created by erikd on 10.11.2024.
//

#include <iostream>
#include "GL.h"


void GLClearError() {
    while(glGetError() != GL_NO_ERROR);
}

void GLLogCall(const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cerr << file << ':' << line << " [OpenGL Error]: " << '(' << error << ')' << std::endl;
    }
}
