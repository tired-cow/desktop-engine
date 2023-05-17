#ifndef _EVENT_MANAGER_H_
#define _EVENT_MANAGER_H_

#include "IListener.h"
#include "Event.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>

class EventManager
{
public:
	static EventManager& GetInstance();
	void RegisterEvent(const std::string&);
	void RemoveEvent(const std::string&);
	void SubscribeToEvent(const std::string&, IListener*);
	void UnsubscribeToEvent(const std::string&, IListener*);
	void NotifyListeners(Event&);
	bool HasEvent(const Event &) const;
	bool HasEvent(const std::string &) const;

public:
	EventManager(const EventManager&) = delete;

private:
	static EventManager m_Instance;
	std::unordered_map<std::string, std::vector<IListener*>> m_EventMap;
	std::queue<Event*> m_EventQueue;

private:
	EventManager() = default;
	
};

#endif