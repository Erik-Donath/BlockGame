//
// Created by erikd on 20.04.2024.
// Refactored by erikd on 27.04.2024.

#pragma once
#include <glad/glad.h>
#include "../../Defines.h"

#define GLCall(func) func; GLCheckError(__FILE__, __LINE__)
#define GLClearError() GLCheckError(__FILE__, __LINE__)
bool GLCheckError(const char* file, int32_t line);

size_t GetSizeOfType(GLenum type);
