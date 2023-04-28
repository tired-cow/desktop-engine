#include "Component.h"
#include "Object.h"

Component::Component(Object *owner)
  : owner{owner} {
}

Component::~Component() {
  
}