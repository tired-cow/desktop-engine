#include <glm/glm.hpp>
#include <GL/glew.h>
#include <xcb/xcb.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <vector>

#include "XWindow.h"


static void create_shader_program(GLuint &);
static void load_verticies_from_obj(const char*, std::vector<float>&, std::vector<unsigned int>&);


int main() {
  std::vector<float> verticies;
  verticies.reserve(25);

  std::vector<unsigned int> indices;
  indices.reserve(25);

  load_verticies_from_obj("breh.obj", verticies, indices);

  verticies.shrink_to_fit();
  indices.shrink_to_fit();

  XWindow window;

  GLenum err = glewInit();
  if (GLEW_OK != err) {
    std::cout << "glewInit failed!\n";
    exit(1);
  }

  GLuint vb;
  glCreateBuffers(1, &vb);
  glNamedBufferStorage(vb, sizeof(float) * verticies.size(), &verticies[0], 0);
  glBindBuffer(GL_ARRAY_BUFFER, vb);

  GLuint ib;
  glCreateBuffers(1, &ib);
  glNamedBufferStorage(ib,  sizeof(unsigned int) * indices.size(), &indices[0], 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);

  GLuint va;
  glGenVertexArrays(1, &va);
  glBindVertexArray(va);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void*)0);
  glEnableVertexAttribArray(0);

  GLuint shader_program_id;
  create_shader_program(shader_program_id);
  glUseProgram(shader_program_id);


  xcb_generic_event_t *xcb_event;
  while (xcb_event = xcb_wait_for_event(window.get_xcb_connection())) {
    switch (xcb_event->response_type & ~0x80) {
    case XCB_EXPOSE:
      static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};
      glClearBufferfv(GL_COLOR, 0, black);
      
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
      glBindVertexArray(va);
      glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);

      glXSwapBuffers(window.get_xorg_display_connection(), window.get_glx_drawable());
      break;
    default:
      break;
    }

    free(xcb_event);
  }
}


//
//  Shader Nonsense
//
static const GLchar *vertex_shader =
" #version 450 core\n\
  in vec4 v_position;\
  void main() {\
    gl_Position = v_position;\
  }\
";

static const GLchar *fragment_shader = 
" #version 450 core\n\
  out vec4 color;\
  void main() {\
    color = vec4(0, 1, 0, 1);\
  }\
";

static bool compile_shader(GLuint &shader_id, GLenum type, const GLchar* src) {
  shader_id = glCreateShader(type);
  glShaderSource(shader_id, 1, &src, NULL);
  glCompileShader(shader_id);

  GLint success;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

  std::fstream log;
  log.open("log.txt", std::ios::out | std::ios::app);
  if (log.is_open()) {
    if (success == GL_TRUE)
      log << "Successfully compiled shader: " << type << std::endl;
    else
      log << "Failed to compile shader: " << type << std::endl;

    log.close();
  }

  return (success == GL_TRUE);
}

static void create_shader_program(GLuint &program_id) {
  bool success;
  
  GLuint v_shader_id;
  success = compile_shader(v_shader_id, GL_VERTEX_SHADER, vertex_shader);// const GLfloat positions[3][2] = {

  GLuint f_shader_id;
  success = compile_shader(f_shader_id, GL_FRAGMENT_SHADER, fragment_shader);

  program_id = glCreateProgram();
  glAttachShader(program_id, v_shader_id);
  glAttachShader(program_id, f_shader_id);

  glLinkProgram(program_id);
}

static void load_verticies_from_obj(const char *file_name, std::vector<float>& verticies, std::vector<unsigned int>& indices) {
  std::ifstream file(file_name);

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream line_stream(line);

    std::string line_cmd;
    line_stream >> line_cmd;

    std::string substr;
    while (getline(line_stream, substr, ' ')) {
        if (substr.length() == 0)
          continue;

        if (line_cmd == "v") {
          float i = std::stof(substr);
          verticies.push_back(i);
        } else if (line_cmd == "f") {
          unsigned int i = (int)substr.at(0) - 48;
          indices.push_back(i);
        }

        
    }
  }

  file.close();
}