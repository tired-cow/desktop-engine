#ifndef _GL_SHADER_H_
#define _GL_SHADER_H_

#include "GLObject.h"
#include <GL/glew.h>
#include <iostream>
#include <string>

class GLShader : public GLObject
{
public:
	const bool Compile();
	void SourceShader(const std::string&);

	const bool IsCompiled() const;
	unsigned int GetShaderType() const;
	

public:
	GLShader(unsigned int);
	~GLShader();
	GLShader(const GLShader&) = delete;
	GLShader& operator=(const GLShader&) = delete;

protected:
	unsigned int m_ShaderType;
	const char *m_ShaderSrc;
	bool m_Compiled;
};

#endif