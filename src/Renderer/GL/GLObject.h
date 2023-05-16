#ifndef _GL_OBJECT_H_
#define _GL_OBJECT_H_

class GLObject 
{
public:
	const unsigned int GetId() const;

public:
	GLObject(unsigned int);
	GLObject();

protected:
	unsigned int m_Id;
};

#endif