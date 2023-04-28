#pragma once

#include <string>
#include <vector>
#include "Component.h"

class Component;

class Object {
protected:
  Object *parent;
  std::string name;
  std::vector<Component*> components;

public:
  Object();
  ~Object();
  void AttachComponent(Component*);
};