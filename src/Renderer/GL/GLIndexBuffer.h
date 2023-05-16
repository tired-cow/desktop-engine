#ifndef _GL_INDEX_BUFFER_H_
#define _GL_INDEX_BUFFER_H_

#include "GLBufferObject.h"
#include <GL/glew.h>
#include <vector>

class GLIndexBuffer : public GLBufferObject 
{
public:
	void BufferData(const std::vector<unsigned int>&);
	void Bind() const override;
	void Unbind() const override;

public:
	GLIndexBuffer() = default;
	GLIndexBuffer(const std::vector<unsigned int>&);
	GLIndexBuffer(const GLIndexBuffer &) = delete;
	GLIndexBuffer &operator=(const GLIndexBuffer &) = delete;
};

#endif