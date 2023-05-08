#ifndef _GL_SHADER_H_
#define _GL_SHADER_H_

#include "GLObject.h"
#include <GL/glew.h>
#include <iostream>
#include <string>

class GLShader : public GLObject 
{
public:
    GLShader(GLenum);
    ~GLShader();
    bool Compile();
    GLenum GetShaderType();
	void SourceShader(const std::string&);

protected:
    GLenum m_ShaderType;
    const char *m_ShaderSrc;
};

#endif