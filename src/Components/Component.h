#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <string>

class Component
{
public:
	const std::string& GetName() const;

public:
	Component(const std::string&);

protected:
	std::string m_Name;

};

#endif