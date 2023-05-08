#include "GLIndexBuffer.h"

GLIndexBuffer::GLIndexBuffer(const std::vector<unsigned int> &indices) 
	: GLBufferObject() 
{
	//this->indices = indices;
	glNamedBufferStorage(id, sizeof(unsigned int) * indices.size(), &indices[0], 0);
}

void GLIndexBuffer::Bind() 
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void GLIndexBuffer::Unbind() 
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}