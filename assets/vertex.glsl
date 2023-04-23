#version 450 core

in vec4 pos;

uniform mat4 transform_mat;

void main() {
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}