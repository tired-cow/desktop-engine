#ifndef _I_LISTENER_H_
#define _I_LISTENER_H_

#include "Event.h"

class IListener
{
public:
	virtual void OnUpdate(Event&) = 0;
};

#endif