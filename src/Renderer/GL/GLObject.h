#ifndef _GL_OBJECT_H_
#define _GL_OBJECT_H_

class GLObject 
{
public:
	const unsigned int GetId() const;

public:
	GLObject(unsigned int);
	GLObject();
	GLObject(const GLObject &) = delete;
	GLObject &operator=(const GLObject &) = delete;

protected:
	unsigned int m_Id;
};

#endif