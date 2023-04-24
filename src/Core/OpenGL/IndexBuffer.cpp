#include "IndexBuffer.h"
#include "GLBufferObject.h"
#include <GL/glew.h>
#include <vector>

IndexBuffer::IndexBuffer(std::vector<unsigned int> &indices) 
  : GLBufferObject() {
  this->indices = indices;
  glNamedBufferStorage(id, sizeof(unsigned int) * indices.size(), &indices[0], 0);
}

void IndexBuffer::bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}