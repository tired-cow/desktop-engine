#include "GLVertexArray.h"

GLVertexArray::GLVertexArray()
	:GLObject() 
{
	glCreateVertexArrays(1, &id);
}

GLVertexArray::~GLVertexArray() 
{
	glDeleteVertexArrays(1, &id);
}

void GLVertexArray::VertexAttribPointer(GLuint index, 
  GLint size, GLenum type, GLboolean normalized, 
  GLsizei stride, const GLvoid *pointer)
{  
	m_AttribIndices.push_back(index);
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void GLVertexArray::Bind() 
{
	glBindVertexArray(id);
  
	for (auto index : m_AttribIndices)
		glEnableVertexAttribArray(index);
}