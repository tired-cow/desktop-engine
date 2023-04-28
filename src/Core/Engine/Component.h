#pragma once

#include "Object.h"

class Object;

class Component {
protected:
  Object *owner;
public:
  Component(Object*);
  ~Component();
};