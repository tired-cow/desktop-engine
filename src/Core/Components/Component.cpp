#include "Component.h"
#include "Engine/Object.h"

Component::Component(Object *owner)
  : owner{owner} {
}

Component::~Component() {
  
}