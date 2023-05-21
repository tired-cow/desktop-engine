#include "GLShaderProgram.h"

GLShaderProgram::GLShaderProgram()
	: GLObject{glCreateProgram()} 
{

}

GLShaderProgram::~GLShaderProgram() 
{
	glDeleteProgram(m_Id);
}

void GLShaderProgram::SetShader(const GLShader &shader) 
{
	unsigned int shaderId = shader.GetId();
	glAttachShader(m_Id, shaderId);
	glLinkProgram(m_Id);
}

void GLShaderProgram::Use() const 
{
	glUseProgram(m_Id);
}

unsigned int GLShaderProgram::GetUniformLocation(const char* name) const
{
	return glGetUniformLocation(m_Id, name);
}