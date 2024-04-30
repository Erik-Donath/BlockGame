#version 330 core
in vec2 vUV;
out vec4 fColor;

uniform sampler2D u_Texture;

void main() {
    fColor = texture(u_Texture, vUV);
}
