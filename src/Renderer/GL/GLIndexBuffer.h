#ifndef _GL_INDEX_BUFFER_H_
#define _GL_INDEX_BUFFER_H_

#include "GLBufferObject.h"
#include <GL/glew.h>
#include <vector>

class GLIndexBuffer : public GLBufferObject 
{
public:
	GLIndexBuffer(const std::vector<unsigned int>&);
	void Bind() override;
	void Unbind() override;

private:
	std::vector<unsigned int> indices;
};

#endif