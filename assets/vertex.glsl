#version 450 core

out vec2 textureCoordinate;
uniform mat4 MVP;

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec2 inTexCoord;

//out vec4 vertexColor;

void main() 
{
    gl_Position = MVP * vec4(vertexPos.x, vertexPos.y, vertexPos.z, 1.0f);
	//vertexColor = vec4(clamp(vertexPos, 0.0f, 1.0f), 1.0f);
	textureCoordinate = inTexCoord;
}
