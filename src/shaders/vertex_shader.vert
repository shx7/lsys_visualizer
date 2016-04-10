#version 130
in vec4 position;
in vec3 color;

out vec3 ColorT;

uniform mat4 view;

void main() {
    gl_Position = view * position;
    ColorT = color;
}
