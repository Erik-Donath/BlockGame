//
// Created by erikd on 30.04.2024.
//

#pragma once
#include <glad/glad.h>
#include "../Defines.h"

typedef u32 glid;
static cstr GetErrorType(GLenum code);
void GLCheckError(cstr file, u32 line);
size_t GetSizeOfType(GLenum type);

//#define GL_Above46
#ifndef GL_Above46
#define GLCall(func) func; GLCheckError(__FILE__, __LINE__)
#define GLClearError() GLCheckError(__FILE__, __LINE__)


#endif