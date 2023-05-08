#ifndef _GL_VERTEX_ARRAY_H_
#define _GL_VERTEX_ARRAY_H_

#include <GL/glew.h>
#include <vector>
#include "GLObject.h"

class GLVertexArray : public GLObject 
{
public:
	GLVertexArray();
	~GLVertexArray();
	void VertexAttribPointer(GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid*);
	void Bind();

private:
	std::vector<unsigned int> m_AttribIndices;
};

#endif