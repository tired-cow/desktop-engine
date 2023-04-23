#pragma once

#include <unordered_map>
#include <GL/glew.h>
#include <fstream>

#include "Shader.h"

class ShaderProgram {
private:
  GLuint program_id;

public:
  ShaderProgram();
  ~ShaderProgram(); 
  
  void set_shader(Shader);
  void use();

  GLuint get_id();
  GLuint get_uniform_location(const char *name);
};