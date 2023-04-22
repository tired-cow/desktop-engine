#pragma once

#include <GL/glew.h>
#include <vector>

class IndexBuffer {
private:
  GLuint id;
  std::vector<unsigned int> indices;

public:
  IndexBuffer(std::vector<unsigned int>&);
  ~IndexBuffer();
  void bind();
};