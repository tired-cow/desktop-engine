#pragma once

#include "Object.h"

class Component {
protected:
  Object *owner;
public:
  Component(Object*);
  ~Component();
};