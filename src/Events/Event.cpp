#include "Event.h"

Event::Event( EventType mask )
	: m_Processed{ false }, m_EventMask{ NonEvent }
{
	m_EventMask &= mask;
}

const bool Event::IsProcessed() const
{
	return m_Processed;
}

const int Event::GetEventMask() const
{
	return m_EventMask;
}

void Event::Process()
{
	m_Processed = true;
}
