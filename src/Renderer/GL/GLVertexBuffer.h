#ifndef _GL_VERTEX_BUFFER_H_
#define _GL_VERTEX_BUFFER_H_

#include "GLBufferObject.h"
#include <GL/glew.h>
#include <vector>

class GLVertexBuffer: public GLBufferObject 
{
public:
	void BufferData(const std::vector<float>&);
	void Bind() const override;
	void Unbind() const override;

public:
	GLVertexBuffer() = default;
	GLVertexBuffer(const std::vector<float>&);
	GLVertexBuffer(const GLVertexBuffer &) = delete;
	GLVertexBuffer &operator=(const GLVertexBuffer &) = delete;
	
};

#endif