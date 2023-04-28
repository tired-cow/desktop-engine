#pragma once

#include "Engine/Object.h"

class Object;

class Component {
protected:
  Object *owner;
public:
  Component(Object*);
  ~Component();
};