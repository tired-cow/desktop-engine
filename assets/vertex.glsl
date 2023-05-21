#version 450 core

layout (location = 0) in vec3 pos;
out vec4 v_color;

uniform mat4 model;
uniform mat4 projection;

void main() {
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);
    v_color = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
}