#shader vertex
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aUV;
out vec2 vUV;

void main() {
    vUV = aUV;
    gl_Position = vec4(aPos.xy, 0.0f, 1.0f);
}

#shader fragment
#version 330 core
in vec2 vUV;
out vec4 fColor;

uniform sampler2D u_Texture;

void main() {
    fColor = texture(u_Texture, vUV);
}
