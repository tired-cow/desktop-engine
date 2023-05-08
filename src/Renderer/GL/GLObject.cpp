#include "GLObject.h"

GLObject::GLObject(unsigned int nId) 
	: id{nId} 
{

}

GLObject::GLObject() : GLObject(0) 
{

}

const unsigned int GLObject::GetId() const
{
	return id;
}