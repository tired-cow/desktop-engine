#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(std::vector<float>& verticies) {
  this->verticies = verticies;
  glCreateBuffers(1, &id);
  glNamedBufferStorage(id, sizeof(float) * verticies.size(), &verticies[0], 0);
}

VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &id);
}

void VertexBuffer::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, id);
}