#pragma once

#include "GLObject.h"
#include "Shader.h"

class ShaderProgram : public GLObject {
private:
  GLuint program_id;

public:
  ShaderProgram();
  ~ShaderProgram(); 
  
  void set_shader(Shader);
  void use();

  unsigned int get_uniform_location(const char *name);
};