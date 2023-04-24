#include "GLObject.h"

GLObject::GLObject(unsigned int n_id) 
  : id{n_id} {

}

GLObject::GLObject() 
  : GLObject(0) {

}

const unsigned int GLObject::get_id() {
  return id;
}