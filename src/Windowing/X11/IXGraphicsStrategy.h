#ifndef _I_X_GRAPHICS_STRATEGY_H_
#define _I_X_GRAPHICS_STRATEGY_H_

#include <GL/glx.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

class IXGraphicsStrategy
{
public:
	virtual XVisualInfo* GetVisualInfo( ) = 0;
	virtual void Setup( ) = 0;
	virtual void SwapBuffers( ) = 0;
};

#endif