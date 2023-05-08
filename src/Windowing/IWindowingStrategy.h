#ifndef _I_WINDOWING_STRATEGY_H_
#define _I_WINDOWING_STRATEGY_H_

#include "Events/Event.h"

class IWindowingStrategy
{
public:
	enum WindowType
	{
		Default, Desktop
	};

	virtual void CreateWindow( const unsigned int& x, const unsigned int& y, 
		const unsigned int& width, const unsigned int& height, 
		IWindowingStrategy::WindowType const& type ) = 0;
	
	virtual Event* GetNextEvent( ) = 0;
	virtual void SwapBuffers( ) = 0;
};

#endif