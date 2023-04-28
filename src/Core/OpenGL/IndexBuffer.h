#pragma once

#include "GLBufferObject.h"
#include <GL/glew.h>
#include <vector>

class IndexBuffer : public GLBufferObject {
private:
  std::vector<unsigned int> indices;

public:
  IndexBuffer(std::vector<unsigned int>&);
  void bind();
  void unbind();
};