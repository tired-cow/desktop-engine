#include "GLShader.h"

GLShader::GLShader(unsigned int GLType) 
	: GLObject(glCreateShader(GLType)), m_ShaderType{GLType}, m_Compiled{false}
{
	
}


GLShader::~GLShader()
{
	glDeleteShader(m_Id);
}


bool GLShader::Compile() 
{
	glCompileShader(m_Id);

	int success;
	glGetShaderiv(m_Id, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
		m_Compiled = false;
	else
		m_Compiled = true;

	return (success == GL_TRUE);
}

GLenum GLShader::GetShaderType() const
{
	return m_ShaderType;
}

void GLShader::SourceShader(const std::string &source)
{
	m_ShaderSrc = source.c_str();
	glShaderSource(m_Id, 1, &m_ShaderSrc, NULL);
}

bool GLShader::IsCompiled() const
{
	return m_Compiled;
}
