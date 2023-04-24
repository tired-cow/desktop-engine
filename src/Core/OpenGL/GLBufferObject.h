#pragma once

#include "GLObject.h"

class GLBufferObject : public GLObject {
protected:
  virtual void bind();
public:
  GLBufferObject();
  ~GLBufferObject();
};