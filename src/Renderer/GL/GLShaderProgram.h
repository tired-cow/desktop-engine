#pragma once

#include "GLObject.h"
#include "GLShader.h"
#include <GL/glew.h>

class GLShaderProgram : public GLObject {
public:
  GLShaderProgram();
  ~GLShaderProgram(); 
  
  void SetShader(const GLShader&);
  void Use();

  unsigned int GetUniformLocation(const char *name);
};