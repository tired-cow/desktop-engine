#pragma once

#include "GLBufferObject.h"
#include <GL/glew.h>
#include <vector>

class VertexBuffer : public GLBufferObject {
private:
  std::vector<float> verticies;

public:
  VertexBuffer(std::vector<float>&);
  void buffer_data();
  void bind();
  void unbind();
};