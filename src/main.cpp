#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <xcb/xcb.h>
#include <iostream>
#include <chrono>
#include <sstream>
#include <vector>


#include "Core/OpenGL/ShaderProgram.h"
#include "Core/OpenGL/VertexBuffer.h"
#include "Core/OpenGL/VertexArray.h"
#include "Core/OpenGL/IndexBuffer.h"
#include "Core/OpenGL/Shader.h"
#include "Core/Windowing/XWindow.h"



static void load_verticies_from_obj(const char*, std::vector<float>&, std::vector<unsigned int>&);

int main() {
  std::vector<float> verticies;
  verticies.reserve(25);
  std::vector<unsigned int> indices;
  indices.reserve(25);
  load_verticies_from_obj("assets/test.obj", verticies, indices);
  verticies.shrink_to_fit();
  indices.shrink_to_fit();

  XWindow window;
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    std::cout << "glewInit failed!\n";
    exit(1);
  }
  
  VertexArray vertex_array;

  VertexBuffer vertex_buffer(verticies);
  IndexBuffer index_buffer(indices);
  

  ShaderProgram s_program;
  Shader vert(GL_VERTEX_SHADER, "assets/vertex.glsl");
  vert.compile();
  s_program.set_shader(vert);
  Shader frag(GL_FRAGMENT_SHADER, "assets/fragment.glsl");
  frag.compile();
  s_program.set_shader(frag);
  s_program.use();


  // glBindVertexArray(va);
  vertex_array.bind();
  vertex_buffer.bind();
  index_buffer.bind();
  vertex_array.vertex_attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void*) 0);
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void*)0);
  // glEnableVertexAttribArray(0);

  // Transformation stuff
  unsigned int model_id = s_program.get_uniform_location("model");
  glm::mat4 model_mat = glm::mat4(1.0f);
  model_mat = glm::translate(model_mat, glm::vec3(0, 0, -2.5f));
  glUniformMatrix4fv(model_id, 1, GL_FALSE, glm::value_ptr(model_mat));


  unsigned int projection_id = s_program.get_uniform_location("projection");
  glm::mat4 proj_mat = glm::mat4(1.0f);
  proj_mat = glm::perspective(30.0f, (float)1920/1080, 0.1f, 100.0f);
  glUniformMatrix4fv(projection_id, 1, GL_FALSE, glm::value_ptr(proj_mat));

  

  glDisable(GL_CULL_FACE);

  float angle = 0.0f;
  // xcb_generic_event_t *xcb_event;
  // while (xcb_event = xcb_wait_for_event(window.get_xcb_connection())) {
  //   switch (xcb_event->response_type & ~0x80) {
  //   case XCB_EXPOSE:
  //     std::cout << "DRAW!\n";
  //     angle += 0.001f;
  //     if (angle >= 360)
  //       angle = 0.0f;

  //     static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};

  //     model_mat = glm::rotate(model_mat, angle * 3.14159265f/180, glm::vec3(0.0f, 0.0f, 1.0f));
  //     glUniformMatrix4fv(model_id, 1, GL_FALSE, glm::value_ptr(model_mat));


  //     glClearBufferfv(GL_COLOR, 0, black);
  //     index_buffer.bind();
      
  //     glBindVertexArray(va);
  //     glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);

  //     glXSwapBuffers(window.get_xorg_display_connection(), window.get_glx_drawable());
  //     break;
  //   default:
  //     break;
  //   }

  //   free(xcb_event);
  // }

  int frame_count;
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  while (1) {
    vertex_array.bind();
    frame_count++;
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    float delta_t = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();

    if (delta_t >= 1) { 
      std::cout << "FPS: " << (float)frame_count/delta_t << std::endl;
      begin = std::chrono::steady_clock::now();
      frame_count = 0;
    }

    angle += 0.001f;
    if (angle >= 360)
      angle = 0.0f;

    static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};

    model_mat = glm::rotate(model_mat, angle * 3.14159265f/180, glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(model_id, 1, GL_FALSE, glm::value_ptr(model_mat));


    glClearBufferfv(GL_COLOR, 0, black);
    index_buffer.bind();
    
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
    glXSwapBuffers(window.get_xorg_display_connection(), window.get_glx_drawable());
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