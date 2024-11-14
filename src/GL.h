//
// Created by erikd on 19.10.2024.
//

//#define debug

#pragma once
#include <cstdint>
#include <stdexcept>
#include "cassert"
#include <glad/glad.h>

typedef uint32_t glid;

void GLClearError();
void GLLogCall(const char* file, int line);

#ifdef debug
#define GLCall(x) GLClearError(); x; GLLogCall(__FILE__, __LINE__)
#else
#define GLCall(x) x
#endif

constexpr size_t SizeofGLType(GLenum type) {
    switch (type) {
        case GL_FLOAT:
            static_assert(sizeof(GLfloat) == sizeof(float), "GLfloat is not the same size as float");
            return sizeof(GLfloat);
        case GL_DOUBLE:
            static_assert(sizeof(GLdouble) == sizeof(double), "GLdouble is not the same size as double");
            return sizeof(GLdouble);
        case GL_INT:
            static_assert(sizeof(GLint) == sizeof(int), "GLint is not the same size as int");
            return sizeof(GLint);
        case GL_UNSIGNED_INT:
            static_assert(sizeof(GLuint) == sizeof(unsigned int), "GLuint is not the same size as unsigned int");
            return sizeof(GLuint);
        case GL_SHORT:
            static_assert(sizeof(GLshort) == sizeof(short), "GLshort is not the same size as short");
            return sizeof(GLshort);
        case GL_UNSIGNED_SHORT:
            static_assert(sizeof(GLushort) == sizeof(unsigned short), "GLushort is not the same size as unsigned short");
            return sizeof(GLushort);
        case GL_BYTE:
            static_assert(sizeof(GLbyte) == sizeof(char), "GLbyte is not the same size as char");
            return sizeof(GLbyte);
        case GL_UNSIGNED_BYTE:
            static_assert(sizeof(GLubyte) == sizeof(unsigned char), "GLubyte is not the same size as unsigned char");
            return sizeof(GLubyte);
        default:
            throw std::invalid_argument("Unsupported OpenGL type");
    }
}