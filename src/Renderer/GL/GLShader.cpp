#include "GLShader.h"

GLShader::GLShader(GLenum type) 
	: GLObject(glCreateShader(type)), m_ShaderType{type} 
{
	
}


GLShader::~GLShader()
{
  glDeleteShader(id);
}


bool GLShader::Compile() {
	glCompileShader(id);

	GLint success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
		throw "Shader failed to compile!";

	return (success == GL_TRUE);
}

GLenum GLShader::GetShaderType() 
{
	return m_ShaderType;
}

void GLShader::SourceShader(const std::string &source)
{
	m_ShaderSrc = source.c_str();
	
	//const char* temp = m_ShaderSrc.c_str();
	glShaderSource(id, 1, &m_ShaderSrc, NULL);
}
