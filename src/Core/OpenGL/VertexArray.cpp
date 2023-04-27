#include "VertexArray.h"
#include <GL/glew.h>
#include "GLObject.h"

VertexArray::VertexArray()
  :GLObject() {
  glCreateVertexArrays(1, &id);
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &id);
}

void VertexArray::vertex_attrib_pointer(GLuint index, 
  GLint size, GLenum type, GLboolean normalized, 
  GLsizei stride, const GLvoid *pointer) {
  
  attribute_indices.push_back(index);
  glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void VertexArray::bind() {
  glBindVertexArray(id);
  
  for (auto index : attribute_indices)
    glEnableVertexAttribArray(index);
}