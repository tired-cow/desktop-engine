#ifndef _I_LISTENER_H_
#define _I_LISTENER_H_

#include "Event.h"

class IListener
{
public:
	virtual void OnUpdate( const Event& ) = 0;
};

#endif