#include "GLShaderProgram.h"

GLShaderProgram::GLShaderProgram()
	: GLObject{glCreateProgram()} 
{

}

GLShaderProgram::~GLShaderProgram() 
{
	glDeleteProgram(id);
}

void GLShaderProgram::SetShader(const GLShader &shader) 
{
	unsigned int shaderId = shader.GetId();
	glAttachShader(id, shaderId);
}

void GLShaderProgram::Use() 
{
	glLinkProgram(id);
	glUseProgram(id);
}

unsigned int GLShaderProgram::GetUniformLocation(const char* name) 
{
	return glGetUniformLocation(id, name);
}