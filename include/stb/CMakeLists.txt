cmake_minimum_required(VERSION 3.28)
project(stb)

add_library(stb include/stb/stb_image.h include/stb/stb_truetype.h src/stb.c)
target_include_directories(stb PUBLIC include/)
