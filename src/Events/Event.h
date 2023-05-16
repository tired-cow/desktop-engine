#ifndef _EVENT_H_
#define _EVENT_H_

#include <string>
#include <memory>

class Event
{
public:
	const std::string& GetId() const;
	std::shared_ptr<void> GetParamters();

public:
	Event(const std::string&, std::shared_ptr<void>);

protected:
	std::string m_Id;
	std::shared_ptr<void> m_Parameters;

};

#endif