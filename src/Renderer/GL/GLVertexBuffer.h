#ifndef _GL_VERTEX_BUFFER_H_
#define _GL_VERTEX_BUFFER_H_

#include "GLBufferObject.h"
#include <GL/glew.h>
#include <vector>

class GLVertexBuffer: public GLBufferObject 
{
public:
	GLVertexBuffer(const std::vector<float>&);
	void Bind() override;
	void Unbind() override;

private:
	std::vector<float> m_Verticies;

};

#endif