cmake_minimum_required(VERSION 3.28)
project(glad)

add_library(glad include/glad/gl.h include/KHR/khrplatform.h src/GL.c)
target_include_directories(glad PUBLIC include/)
