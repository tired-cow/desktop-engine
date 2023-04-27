#include "Object.h"

Object::Object() 
  : parent{nullptr}, name{"Root"} {

}

Object::~Object() {
  delete parent;
}