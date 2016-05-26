#version 130
in vec4 position;
in vec3 color;

out vec3 ColorT;

uniform mat4 view;
uniform mat4 proj;

void main() {
    gl_Position = proj * view * position;
    ColorT = color;
}
