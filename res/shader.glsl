#shader vertex
#version 330 core
layout (location = 0) in vec4 aPos;
out vec4 vPos;

void main() {
    vPos = aPos;
    gl_Position = aPos;
}

#shader fragment
#version 330 core
in vec4 vPos;
out vec4 FragColor;

void main() {
    FragColor = vec4((vPos.r + 1) / 2, (vPos.g + 1) / 2, 0.0f, 1.0f);
}
