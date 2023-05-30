#version 450 core

uniform sampler2D tex;

layout (location = 0) out vec4 color;
in vec2 textureCoordinate;
//in vec4 vertexColor;

void main() 
{
    color = texture2D(tex, textureCoordinate);
	//color = vertexColor;
}