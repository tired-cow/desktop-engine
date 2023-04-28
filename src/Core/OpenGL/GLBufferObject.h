#pragma once

#include "GLObject.h"

class GLBufferObject : public GLObject {
protected:
  virtual void bind();
  virtual void unbind();
  virtual void buffer_data();
public:
  GLBufferObject();
  ~GLBufferObject();
};