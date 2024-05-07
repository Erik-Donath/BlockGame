#version 330 core

in vec4 v_color;
out vec4 f_color;

void main() {
    f_color = 1 - v_color;
    f_color.a = 1.0f;
    //f_color = vec4(1.0f, 1.0f, 1.0f, 1.0f); // White
}
