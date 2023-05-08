#ifndef _GL_OBJECT_H_
#define _GL_OBJECT_H_

class GLObject 
{
public:
	GLObject(unsigned int);
	GLObject();
	const unsigned int GetId() const;

protected:
	unsigned int id;
};

#endif