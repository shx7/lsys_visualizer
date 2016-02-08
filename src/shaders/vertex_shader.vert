#version 130
in vec4 position;
in vec3 color;

out vec3 ColorT;

void main() {
    gl_Position = position;
    ColorT = color;
}
