#include "Shader.h"

Shader::Shader(GLenum type, const char *file_path) 
  : shader_type{type} {
  shader_id = glCreateShader(type);
  get_src_from_file(file_path);
  //std::cout<< shader_src <<std::endl;
}


Shader::Shader() {
  Shader(GL_VERTEX_SHADER, nullptr);
}

Shader::~Shader() {
  glDeleteShader(shader_id);
}


bool Shader::compile() {
  glCompileShader(shader_id);

  GLint success;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

  std::fstream log;
  log.open("log.txt", std::ios::out | std::ios::app);
  if (log.is_open()) {
      if (success == GL_TRUE)
      log << "Successfully compiled shader: " << shader_id << std::endl;
      else
      log << "Failed to compile shader: " << shader_id << std::endl;

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
  glShaderSource(shader_id, 1, &temp, NULL);
}


GLenum Shader::get_shader_type() {
  return shader_type;
}


GLuint Shader::get_shader_id() {
  return shader_id;
}