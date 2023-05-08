#include "GLVertexBuffer.h"

GLVertexBuffer::GLVertexBuffer(const std::vector<float>& verticies)
	: GLBufferObject() 
{
	//m_Verticies = verticies;
	glNamedBufferStorage(id, sizeof(float) * verticies.size(), &verticies[0], 0);
}

void GLVertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void GLVertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
