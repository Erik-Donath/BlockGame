//
// Created by erikd on 30.04.2024.
//

#pragma once
#include <glad/glad.h>
#include "../Defines.h"

//#define GL_Above46 // Falls das Projekt OpenGL Version 4.6 oder höher verwendet, können andere Funktionen genutzt werden.

namespace Rendering {
    typedef u32 glid;

    void GLCheckError(cstr file, u32 line);

    size_t GetSizeOfType(GLenum type);

    cstr GetErrorType(GLenum code);

    cstr GetShaderType(GLenum type);
}

#ifndef GL_Above46
#define GLCall(func) func; Rendering::GLCheckError(__FILE__, __LINE__)
#define GLClearError() Rendering::GLCheckError(__FILE__, __LINE__)
#else
#define GLCall(func) func
#define GLClearError() Rendering::GLCheckError(__FILE__, __LINE__)
#endif
