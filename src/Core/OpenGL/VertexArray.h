#pragma once

#include <GL/glew.h>
#include <vector>
#include "GLObject.h"

class VertexArray : public GLObject {
private:
  std::vector<unsigned int> attribute_indices;

public:
  VertexArray();
  ~VertexArray();
  void vertex_attrib_pointer(GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid*);
  void bind();
};