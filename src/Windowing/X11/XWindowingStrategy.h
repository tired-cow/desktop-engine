#ifndef _X_WINDOWING_STRATEGY_H_
#define _X_WINDOWING_STRATEGY_H_

#include "IWindowingStrategy.h"
#include "GLXGraphicsStrategy.h"
#include "Events/Event.h"
#include <memory>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>


class XWindowingStrategy : public IWindowingStrategy
{
public:
	void CreateWindow( const unsigned int& x, const unsigned int& y, 
		const unsigned int& width, const unsigned int& height, 
		IWindowingStrategy::WindowType const& type ) override;
	
	Event* GetNextEvent( ) override;

	void SwapBuffers( );

protected:
	std::unique_ptr<IXGraphicsStrategy> m_GraphicsStrat;

	Display 	*m_Display;
	XVisualInfo *m_VisualInfo;
	Window   	 m_Window;
};

#endif