#include "VertexBuffer.h"
#include "GLBufferObject.h"
#include <GL/glew.h>
#include <vector>

VertexBuffer::VertexBuffer(std::vector<float>& verticies)
  : GLBufferObject() {
  this->verticies = verticies;
  glNamedBufferStorage(id, sizeof(float) * verticies.size(), &verticies[0], 0);
}

void VertexBuffer::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}