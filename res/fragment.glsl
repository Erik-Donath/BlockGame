#version 330 core
in vec3 fColor;
out vec4 oColor;

void main() {
    oColor = vec4(fColor, 1.0);
}
