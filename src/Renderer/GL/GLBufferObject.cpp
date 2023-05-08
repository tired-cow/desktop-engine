#include "GLBufferObject.h"

GLBufferObject::GLBufferObject()
	: GLObject() 
{
	glCreateBuffers(1, &id);
}

GLBufferObject::~GLBufferObject()
{
	glDeleteBuffers(1, &id);
}