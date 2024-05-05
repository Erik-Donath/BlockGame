//
// Created by erikd on 30.04.2024.
//

#pragma once
#include "glad/glad.h"
#include "../../Defines.h"

// Falls das Projekt OpenGL Version 4.6 oder höher verwendet, können andere Funktionen genutzt werden.
//#define GL_Above46

namespace Engine::GL {
    typedef u32 glId;

    class GL {
    public:
        static void CheckError(cstr file, u32 line);
        static size_t GetSizeOfType(GLenum type);
        static cstr GetErrorType(GLenum code);
        static cstr GetShaderType(GLenum type);
    };
}

#ifndef GL_Above46
#define GLCall(func) func; Engine::GL::GL::CheckError(__FILE__, __LINE__)
#define GLClearError() Engine::GL::GL::CheckError(__FILE__, __LINE__)
#else
#define GLCall(func) func
#define GLClearError() Engine::GL::GL::CheckError(__FILE__, __LINE__)
#endif
