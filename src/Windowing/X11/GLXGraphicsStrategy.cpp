#include "GLXGraphicsStrategy.h"

GLXGraphicsStrategy::GLXGraphicsStrategy( Display* display, Window* window )
{
	m_Display = display;
	m_Window = window;
}

XVisualInfo* GLXGraphicsStrategy::GetVisualInfo( )
{
	m_VisualInfo = glXChooseVisual(m_Display, 0, m_Attributes);
	return m_VisualInfo;
}

void GLXGraphicsStrategy::Setup( )
{
	m_Context = glXCreateContext( m_Display, m_VisualInfo, NULL, GL_TRUE );
	glXMakeCurrent( m_Display, *m_Window, m_Context );
}

void GLXGraphicsStrategy::SwapBuffers( )
{
	glXSwapBuffers( m_Display, *m_Window );
}
