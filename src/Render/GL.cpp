//
// Created by erikd on 30.04.2024.
//

#include <iostream>
#include "GL.h"

cstr GetErrorType(GLenum code) {
    switch (code) {
        case GL_NO_ERROR:                       return "GL_NO_ERROR";
        case GL_INVALID_ENUM:                   return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:                  return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:              return "GL_INVALID_OPERATION";
        case GL_INVALID_FRAMEBUFFER_OPERATION:  return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_OUT_OF_MEMORY:                  return "GL_OUT_OF_MEMORY";
        case GL_STACK_UNDERFLOW:                return "GL_STACK_UNDERFLOW";
        case GL_STACK_OVERFLOW:                 return "GL_STACK_OVERFLOW";
        case GL_CONTEXT_LOST:                   return "GL_CONTEXT_LOST";
        case GL_TABLE_TOO_LARGE:                return "GL_TABLE_TOO_LARGE";
        default:                                return "UNKNOWN_ERROR";
    }
}

void GLCheckError(cstr file, u32 line) {
    while (GLenum code = glGetError()) {
        std::cerr << "Error: GL " << code << ": " << GetErrorType(code) << " at " << file << ':' << line << std::endl;
    }
}

size_t GetSizeOfType(GLenum type) {
    switch (type) {
        case GL_BOOL: return sizeof(GLboolean);
        case GL_BYTE: return sizeof(GLbyte);
        case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
        case GL_SHORT: return sizeof(GLshort);
        case GL_UNSIGNED_SHORT: return sizeof(GLushort);
        case GL_INT: return sizeof(GLint);
        case GL_UNSIGNED_INT: return sizeof(GLuint);
        case GL_FIXED: return sizeof(GLfixed);
        case GL_FLOAT: return sizeof(GLfloat);
        case GL_DOUBLE: return sizeof(GLdouble);

        case GL_HALF_FLOAT_ARB: return sizeof(GLhalfARB);
        default: return 1;
    }
}

/* Types that GetSizeOfType does not supported:
     * GLchar
     * GLint64
     * GLuint64
     * GLsizei
     * GLenum
     * GLintptr
     * GLsizeiptr
     * GLsync
     * GLbitfield
     * GLhalf
     * GLclampf
     * GLclampd
     * GLDEBUGPROC
     * GLDEBUGPROCFunc

     * GLcharARB
     * GLint64EXT
     * GLuint64EXT
     * GLintptrARB
     * GLsizeiptrARB
     * GLDEBUGPROCAMD
     * GLDEBUGPROCAMDFunc
     * makeGLDEBUGPROCAMD
     * GLDEBUGPROCARB
     * GLDEBUGPROCARBFunc
     * makeGLDEBUGPROCARB
     * GLDEBUGPROCKHR
     * GLDEBUGPROCKHRFunc
     * makeGLDEBUGPROCKHR

     * [Types from various extensions]
*/
