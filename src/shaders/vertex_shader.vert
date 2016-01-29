#version 130
in vec2 pos;
in vec3 color;

out vec3 ColorT;

uniform mat4 transformMatrix;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main() {
    ColorT = color;
    gl_Position = projMatrix * viewMatrix * transformMatrix * vec4(pos, 0.0, 1.0);
    //gl_Position = transformMatrix * vec4(pos, 0.0, 1.0);
}
