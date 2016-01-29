#version 130

in vec3 ColorT;
//uniform vec3 triangleColor;

void main() {
    gl_FragColor = vec4(ColorT, 1.0);
}
