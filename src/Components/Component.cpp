#include "Component.h"

Component::Component(const std::string &name)
	: m_Name{name}
{
}

const std::string &Component::GetName() const
{
	return m_Name;
}