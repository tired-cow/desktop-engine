#ifndef _GL_BUFFER_OBJECT_H_
#define _GL_BUFFER_OBJECT_H_

#include "GLObject.h"
#include <GL/glew.h>

class GLBufferObject : public GLObject 
{
public:
	GLBufferObject();
	~GLBufferObject();

protected:
	virtual void Bind() = 0;
	virtual void Unbind() = 0;
};

#endif 