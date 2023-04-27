#include "ShaderProgram.h"
#include <GL/glew.h>

ShaderProgram::ShaderProgram()
  : GLObject{glCreateProgram()} {

}

ShaderProgram::~ShaderProgram() {
   glDeleteProgram(id);
}

void ShaderProgram::set_shader(Shader shader) {
  GLuint shader_id = shader.get_id();
  glAttachShader(id, shader_id);
}

void ShaderProgram::use() {
  glLinkProgram(id);
  glUseProgram(id);
}

unsigned int ShaderProgram::get_uniform_location(const char* name) {
  return glGetUniformLocation(id, name);
}