#include "GLIndexBuffer.h"

GLIndexBuffer::GLIndexBuffer(const std::vector<unsigned int> &indices) 
	: GLBufferObject() 
{
	BufferData(indices);
}

void GLIndexBuffer::BufferData(const std::vector<unsigned int> &indices)
{
	Bind();
	glNamedBufferStorage(m_Id, sizeof(unsigned int) * indices.size(), &indices[0], 0);
}

void GLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
}

void GLIndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}