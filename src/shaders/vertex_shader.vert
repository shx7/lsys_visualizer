#version 130
in vec3 position;
in vec3 color;

out vec3 ColorT;

void main() {
    gl_Position = vec4(position, 1.0);
    ColorT = color;
}
