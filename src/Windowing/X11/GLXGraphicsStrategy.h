#ifndef _GLX_GRAPHICS_STRATEGY_H_
#define _GLX_GRAPHICS_STRATEGY_H_

#include "IXGraphicsStrategy.h"
#include "GLXGraphicsStrategy.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

class GLXGraphicsStrategy : public IXGraphicsStrategy 
{
public:
	GLXGraphicsStrategy( Display* display, Window* window );
	XVisualInfo* GetVisualInfo( ) override;
	void Setup( ) override;
	void SwapBuffers( ) override;

protected:
	int m_Attributes[5] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	Display* m_Display;
	Window* m_Window;
	XVisualInfo* m_VisualInfo;
	GLXContext m_Context;
};

#endif