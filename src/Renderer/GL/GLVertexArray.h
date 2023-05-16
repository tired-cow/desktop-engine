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
	inline int CalculateStride() const;

protected:
	std::vector<int> m_Attributes;
};

#endif