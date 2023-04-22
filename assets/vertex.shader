#version 450 core

in vec4 v_position;
void main() {
    gl_Position = v_position;
}