#include "EventManager.h"

void EventManager::AddListner( IListener *l, Event::EventType t)
{
	m_Listeners[l] = t;
}

void EventManager::RemoveListener( IListener *l )
{
	m_Listeners.erase( l );
}

void EventManager::NotifyListeners( Event *event )
{
	for (const auto & [ listener, subscribedMasks ] : m_Listeners) 
	{
		if ((subscribedMasks & event->GetEventMask()) == Event::KeyPressed)
			listener->OnUpdate( *event );
	}
}
