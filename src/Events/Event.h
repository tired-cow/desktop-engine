#ifndef _EVENT_H_
#define _EVENT_H_

class Event
{
public:
	enum EventType
	{
		NonEvent = 0,
		KeyPressed = 2, KeyReleased = 4
	};

	[[nodiscard]] const bool IsProcessed( ) const;
	[[nodiscard]] const int GetEventMask( ) const;

	Event( EventType );
	void Process( );

protected:
	bool m_Processed;
	int m_EventMask;
};

#endif