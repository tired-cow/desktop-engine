#ifndef _GL_VERTEX_ARRAY_H_
#define _GL_VERTEX_ARRAY_H_

#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include "GLObject.h"
#include "GLBufferObject.h"

class GLVertexArray : public GLObject 
{
public:
	void AddVertexAttribute(int, unsigned int);
	void Bind() const;
	void Unbind() const;

public:
	GLVertexArray();
	~GLVertexArray();
	GLVertexArray(const GLVertexArray &) = delete;
	GLVertexArray &operator=(const GLVertexArray &) = delete;

protected:
	struct VertexAttribData
	{
		unsigned int m_Count;
		unsigned int m_GLType;
		unsigned int m_Size;

		VertexAttribData(unsigned int GLType, unsigned int count)
			: m_Count{count}, m_GLType{GLType}, m_Size{CalculateSizeFromGLType(GLType, count)}
		{

		}

		unsigned int CalculateSizeFromGLType(unsigned int GLType, unsigned int count) const
		{
				if (count <= 0)
				{
					std::cout << "Invalid count\n";
					exit(1);
				}

				switch (GLType)
				{
					case GL_FLOAT:
						return sizeof(float) * count;
					
					case GL_UNSIGNED_INT:
						return sizeof(unsigned int) * count;
					
					default:
						std::cout << "Invalid GLType\n";
						exit(1);
				}
		}
	};

protected:
	inline int CalculateStride() const;
	void RecalcVertexAttributeArray();

protected:
	// std::vector<std::vector<int>> m_Attributes;
	//std::vector<int> m_Attributes;
	std::vector<VertexAttribData> m_Attributes;

};

#endif