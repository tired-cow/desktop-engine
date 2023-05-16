#include "GLVertexArray.h"

GLVertexArray::GLVertexArray() : GLObject()
{
	glCreateVertexArrays(1, &m_Id);
}

GLVertexArray::~GLVertexArray() 
{
	glDeleteVertexArrays(1, &m_Id);
}

// void GLVertexArray::VertexAttribPointer(GLuint index, 
// 	GLint size, GLenum type, GLboolean normalized, 
// 	GLsizei stride, const GLvoid *pointer)
// {  
// 	m_AttribIndices.push_back(index);
// 	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
// }

void GLVertexArray::Bind() const
{
	glBindVertexArray(m_Id);
}

void GLVertexArray::Unbind() const
{
	glBindVertexArray(0);
}

inline int GLVertexArray::CalculateStride() const
{
	int sum = 0;
	for (int i : m_Attributes)
		sum += i;

	return sum;
}

void GLVertexArray::AddVertexAttribute(int count, unsigned int GLType)
{
	if (count > 4 || count <= 0) 
	{
		std::cout << "Vertex attribute size " << count << " is not supported!\n";
		exit(1);
	}

	int offset = CalculateStride();

	switch (GLType)
	{
	case GL_FLOAT:
		m_Attributes.push_back(sizeof(float) * count);
		break;
	case GL_UNSIGNED_INT:
		m_Attributes.push_back(sizeof(unsigned int) * count);
		break;
	}

	Bind();
	int size = CalculateStride();
	glVertexAttribPointer(m_Attributes.size() - 1, count, GLType, false, CalculateStride(), (void *)offset);
	glEnableVertexAttribArray(m_Attributes.size() - 1);
	Unbind();
}

// template<typename T>
// void GLVertexArray::AttachBufferObject(const GLBufferObject &bufferObj)
// {
// 	Bind();
// 	(T*)(&bufferObj)->Bind();
// 	Unbind();
// }

// void GLVertexArray::DettachBufferObject(const GLBufferObject &bufferObj)
// {
// 	Bind();
// 	bufferObj.Unbind();
// 	Unbind();
// }
