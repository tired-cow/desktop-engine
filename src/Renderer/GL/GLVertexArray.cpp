#include "GLVertexArray.h"

GLVertexArray::GLVertexArray() : GLObject()
{
	glCreateVertexArrays(1, &m_Id);
}

GLVertexArray::~GLVertexArray() 
{
	glDeleteVertexArrays(1, &m_Id);
}

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
	for (VertexAttribData i : m_Attributes)
		sum += i.m_Size;

	return sum;
}

void GLVertexArray::RecalcVertexAttributeArray()
{
	int stride = CalculateStride();

	for (unsigned int i = 0; i < m_Attributes.size(); i++)
	{
		VertexAttribData data = m_Attributes.at(i);
		glVertexAttribPointer(i, data.m_Count, data.m_GLType, false, stride, (void*)0);
		glEnableVertexAttribArray(i);
	}
}

void GLVertexArray::AddVertexAttribute(int count, unsigned int GLType)
{
	if (count > 4 || count <= 0) 
	{
		std::cout << "Vertex attribute size " << count << " is not supported!\n";
		exit(1);
	}

	VertexAttribData data(GLType, count);
	m_Attributes.push_back(data);

	Bind();
	RecalcVertexAttributeArray();
	Unbind();
}