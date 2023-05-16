#include "XWindowingStrategy.h"

void XWindowingStrategy::CreateWindow( const unsigned int& x, const unsigned int& y, 
		const unsigned int& width, const unsigned int& height, 
		IWindowingStrategy::WindowType const& type ) 
{
	m_Display = XOpenDisplay( NULL );
	if (m_Display == NULL)
		throw "Could not connect to X-Server!";

	{
		GLXGraphicsStrategy *temp = new GLXGraphicsStrategy( m_Display, &m_Window );
		m_GraphicsStrat = std::unique_ptr<GLXGraphicsStrategy>(temp);
	}
	
	m_VisualInfo = m_GraphicsStrat->GetVisualInfo();
	if (m_VisualInfo == NULL)
		throw "Could not find an appropriate visual!";
	
	Colormap colormap = XCreateColormap( m_Display, DefaultRootWindow( m_Display ), m_VisualInfo->visual, AllocNone );
	XSetWindowAttributes xWindowAttribs;
	xWindowAttribs.colormap = colormap;
	xWindowAttribs.event_mask = ExposureMask | KeyPressMask | PointerMotionMask;

	m_Window = XCreateWindow( m_Display, DefaultRootWindow( m_Display ), x, y, 
			width, height, 0, m_VisualInfo->depth, InputOutput, m_VisualInfo->visual, 
			CWColormap | CWEventMask, &xWindowAttribs 
	);

	if (type == IWindowingStrategy::Desktop)
    {
        Atom windowType = XInternAtom( m_Display, "_NET_WM_WINDOW_TYPE", false );
        Atom atomType[] = {XInternAtom( m_Display, "_NET_WM_WINDOW_TYPE_DESKTOP", false )};
        XChangeProperty(m_Display, m_Window, windowType, XA_ATOM, 32, PropModeReplace, (unsigned char *)atomType, 1L);
	}

	XMapWindow(m_Display, m_Window);
	m_GraphicsStrat->Setup();
	XFlush(m_Display);
}

Event XWindowingStrategy::GetNextEvent()
{
	XEvent event;
	XNextEvent(m_Display, &event);

	switch(event.type)
	{
		case KeyPress:
		{
			std::shared_ptr<unsigned int> data = std::make_shared<unsigned int>(event.xkey.keycode);
			return Event("KeyPressed", data);
		}
		case MotionNotify:
		{
			std::vector<int> t {event.xmotion.x, event.xmotion.y};
			std::cout << event.xmotion.x << " " << event.xmotion.y << std::endl;
			std::shared_ptr< std::vector<int> > data = std::make_shared< std::vector<int> >(t);
			return Event("MouseMoved", data);
		}
		default:
			return Event("None", nullptr);
	}
}

void XWindowingStrategy::SwapBuffers()
{
	m_GraphicsStrat->SwapBuffers();
}
