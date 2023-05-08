#ifndef _EVENT_MANAGER_H_
#define _EVENT_MANAGER_H_

#include "IListener.h"
#include "Event.h"
#include <unordered_map>
#include <queue>

class EventManager
{
public:
	
	void AddListner( IListener*, Event::EventType );
	void RemoveListener( IListener* );
	void NotifyListeners( Event* );

protected:
	std::unordered_map<IListener*, Event::EventType> m_Listeners;
};

#endif