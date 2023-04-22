#pragma once

#include <unordered_map>
#include <GL/glew.h>
#include <fstream>

#include "Shader.h"

class ShaderProgram {
private:
  GLuint program_id;
  // std::unordered_map<GLenum, Shader> attached_shaders;

public:
  ShaderProgram();
  ~ShaderProgram(); 
  void set_shader(Shader);
  void use();
};