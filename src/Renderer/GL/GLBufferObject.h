#ifndef _GL_BUFFER_OBJECT_H_
#define _GL_BUFFER_OBJECT_H_

#include "GLObject.h"
#include <GL/glew.h>

class GLBufferObject : public GLObject 
{
public:
	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;
	void BufferData();

public:
	GLBufferObject();
	~GLBufferObject();
	GLBufferObject(const GLBufferObject &) = delete;
	GLBufferObject &operator=(const GLBufferObject &) = delete;
};

#endif 