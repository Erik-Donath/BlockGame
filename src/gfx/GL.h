//
// Created by erikd on 20.04.2024.
//

#pragma once
#include <glad/glad.h>

#define GLCall(func) func; GLCheckError(__FILE__, __LINE__)
#define GLClearError() GLCheckError(__FILE__, __LINE__)
bool GLCheckError(const char* file, int line);

size_t GetSizeOfType(GLenum type);
