#include "GLVertexBuffer.h"

GLVertexBuffer::GLVertexBuffer(const std::vector<float>& vertices)
	: GLBufferObject() 
{
	BufferData(vertices);
}

void GLVertexBuffer::BufferData(const std::vector<float> &vertices)
{
	Bind();	
	glNamedBufferStorage(m_Id, sizeof(float) * vertices.size(), &vertices[0], 0);
}

void GLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Id);
}

void GLVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
