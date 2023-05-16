#include "GLBufferObject.h"

GLBufferObject::GLBufferObject()
	: GLObject() 
{
	glCreateBuffers(1, &m_Id);
}

GLBufferObject::~GLBufferObject()
{
	glDeleteBuffers(1, &m_Id);
}

void GLBufferObject::BufferData()
{
}
