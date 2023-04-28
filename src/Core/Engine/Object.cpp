#include "Object.h"
#include "Component.h"
#include <vector>

Object::Object() 
  : parent{nullptr}, name{"Root"} {

}

Object::~Object() {

}

void Object::AttachComponent(Component* comp) {
  components.push_back(comp);
}