#pragma once

#include "GLObject.h"
#include "GLShader.h"
#include <GL/glew.h>

class GLShaderProgram : public GLObject {
public:
	void SetShader(const GLShader&);

	void Use() const;
	unsigned int GetUniformLocation(const char *name) const;

public:
	GLShaderProgram();
	~GLShaderProgram(); 
	GLShaderProgram(const GLShaderProgram &) = delete;
	GLShaderProgram &operator=(const GLShaderProgram &) = delete;
};