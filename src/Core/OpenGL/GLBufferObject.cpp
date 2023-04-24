#include "GLBufferObject.h"
#include "GLObject.h"
#include <GL/glew.h>

GLBufferObject::GLBufferObject()
  : GLObject() {
  glCreateBuffers(1, &id);
}

GLBufferObject::~GLBufferObject() {
  glDeleteBuffers(1, &id);
}

void GLBufferObject::bind() {

}