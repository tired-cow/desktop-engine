#include "GLObject.h"

GLObject::GLObject(unsigned int nId) 
	: m_Id{nId} 
{

}

GLObject::GLObject() : GLObject(0) 
{

}

const unsigned int GLObject::GetId() const
{
	return m_Id;
}