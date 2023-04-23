#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
  program_id = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
   glDeleteProgram(program_id);
}

void ShaderProgram::set_shader(Shader shader) {
  //GLenum shader_type = shader.get_shader_type();
  GLuint shader_id = shader.get_shader_id();

  // if (attached_shaders.find(shader_type) != attached_shaders.end())
  //   glDetachShader(program_id, shader_id);

  // attached_shaders[shader_type] = shader;
  glAttachShader(program_id, shader_id);
}

void ShaderProgram::use() {
  glLinkProgram(program_id);
  glUseProgram(program_id);
}

GLuint ShaderProgram::get_id() {
  return program_id;
}

GLuint ShaderProgram::get_uniform_location(const char* name) {
  return glGetUniformLocation(program_id, name);
}