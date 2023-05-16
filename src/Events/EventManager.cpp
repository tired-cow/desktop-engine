#include "EventManager.h"

EventManager EventManager::m_Instance;

EventManager &EventManager::GetInstance()
{
	return m_Instance;
}

void EventManager::RegisterEvent(const std::string &eventName)
{
	if (!HasEvent(eventName))
		m_EventMap[eventName];
}

void EventManager::RemoveEvent(const std::string &eventName)
{
	if (HasEvent(eventName) == false)
	{
		std::cout << "Could not remove event " << eventName << std::endl;
		return;
	}

	m_EventMap.erase(eventName);
}

void EventManager::SubscribeToEvent(const std::string &eventName, IListener *listener)
{
	if (HasEvent(eventName) == false) 
	{
		std::cout << "There is no event " << eventName << " to add a listener to.\n";
		return;
	}

	m_EventMap[eventName].push_back(listener);
}

void EventManager::UnsubscribeToEvent(const std::string &eventName, IListener *listener)
{
	if (HasEvent(eventName) == false)
	{
		std::cout << "There is no event " << eventName << " to remove a listener from.\n";
		return;
	}

	std::vector<IListener*> &listenerVec = m_EventMap[eventName];
	for (int i = 0; i < listenerVec.size(); i++)
		if (listenerVec.at(i) == listener)
			listenerVec.erase(listenerVec.begin() + i);
}

void EventManager::NotifyListeners(Event &event)
{
	if (HasEvent(event) == false)
	{
		std::cout << "There is no event " << event.GetId() << " notify listeners of.\n";
		return;
	}

	for (auto listener : m_EventMap[event.GetId()])
		listener->OnUpdate(event);
}

bool EventManager::HasEvent(const Event &event)
{
	return HasEvent(event.GetId());
}

bool EventManager::HasEvent(const std::string &id)
{
	return !(m_EventMap.find(id) == m_EventMap.end());
}
