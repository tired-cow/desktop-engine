#include "Event.h"


const std::string& Event::GetId() const
{
	return m_Id;
}

std::shared_ptr<void> Event::GetParamters()
{
	return m_Parameters;
}

Event::Event(const std::string &string, std::shared_ptr<void> params)
	: m_Id{string}, m_Parameters{params}
{
}
