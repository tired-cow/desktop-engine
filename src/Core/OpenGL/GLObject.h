#pragma once

class GLObject {
protected:
  unsigned int id;

public:
  GLObject(unsigned int);
  GLObject();
  const unsigned int get_id();
};