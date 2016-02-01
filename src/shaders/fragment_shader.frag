#version 130

in vec3 ColorT;

void main() {
    gl_FragColor = vec4(ColorT, 1.0);
}
