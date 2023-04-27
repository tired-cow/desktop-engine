#pragma once

#include <string>
#include <vector>

class Object {
protected:
  Object *parent;
  std::string name;

public:
  Object();
  ~Object();
};