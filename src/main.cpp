#include <glm/glm.hpp>
#include <GL/glew.h>
#include <xcb/xcb.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <vector>

#include "XWindow.h"
#include "Shader.h"
#include "ShaderProgram.h"


static void load_verticies_from_obj(const char*, std::vector<float>&, std::vector<unsigned int>&);

int main() {
  std::vector<float> verticies;
  verticies.reserve(25);

  std::vector<unsigned int> indices;
  indices.reserve(25);

  load_verticies_from_obj("assets/breh.obj", verticies, indices);

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

  Shader vert(GL_VERTEX_SHADER, "assets/vertex.shader");
  vert.compile();

  Shader frag(GL_FRAGMENT_SHADER, "assets/fragment.shader");
  frag.compile();

  ShaderProgram s_program;
  s_program.set_shader(vert);
  s_program.set_shader(frag);

  s_program.use();

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