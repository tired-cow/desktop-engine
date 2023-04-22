#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(std::vector<unsigned int> &indices) {
  this->indices = indices;
  glCreateBuffers(1, &id);
  glNamedBufferStorage(id, sizeof(unsigned int) * indices.size(), &indices[0], 0);
}

IndexBuffer::~IndexBuffer() {
  glDeleteBuffers(1, &id);
}

void IndexBuffer::bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}