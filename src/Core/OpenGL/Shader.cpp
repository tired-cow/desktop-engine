#include "Shader.h"

Shader::Shader(GLenum type, const char *file_path) 
  : GLObject(glCreateShader(type)), shader_type{type} {
  get_src_from_file(file_path);
}


Shader::~Shader() {
  glDeleteShader(id);
}


bool Shader::compile() {
  glCompileShader(id);

  GLint success;
  glGetShaderiv(id, GL_COMPILE_STATUS, &success);

  std::fstream log;
  log.open("log.txt", std::ios::out | std::ios::app);
  if (log.is_open()) {
      if (success == GL_TRUE)
      log << "Successfully compiled shader: " << id << std::endl;
      else
      log << "Failed to compile shader: " << id << std::endl;

      log.close();
  }

  return (success == GL_TRUE);
}


void Shader::get_src_from_file(const char file_path[]) {
  std::ifstream ifs(file_path);
  shader_src = std::string(
      (std::istreambuf_iterator<char>(ifs)),
      (std::istreambuf_iterator<char>())
  );

  const char* temp = shader_src.c_str();
  glShaderSource(id, 1, &temp, NULL);
}


GLenum Shader::get_shader_type() {
  return shader_type;
}