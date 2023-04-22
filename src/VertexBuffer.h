#pragma once

#include <GL/glew.h>
#include <vector>

class VertexBuffer {
private:
  GLuint id;
  std::vector<float> verticies;

public:
  VertexBuffer(std::vector<float>&);
  ~VertexBuffer();

  void bind();
};