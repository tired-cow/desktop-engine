#include "EngineWindow.h"

EngineWindow::EngineWindow( ) 
{
	m_WindowingStrategy = std::make_unique<XWindowingStrategy>();
}

void EngineWindow::SetStrategy( IWindowingStrategy *strategy )
{
	if (strategy == nullptr)
		throw "Strategy cannot be null!";
	
	if (m_WindowingStrategy != nullptr)
		m_WindowingStrategy.release( );

	m_WindowingStrategy = std::unique_ptr<IWindowingStrategy>( strategy );
}

void EngineWindow::Initialize( const unsigned int& x, const unsigned int& y, 
		const unsigned int& width, const unsigned int& height, 
		IWindowingStrategy::WindowType const& type )
{
	m_WindowingStrategy->CreateWindow( x, y, width, height, type );
}

void EngineWindow::SwapBuffers( )
{
	m_WindowingStrategy->SwapBuffers( );
}

const Event& EngineWindow::GetNextEvent( )
{
	return *(m_WindowingStrategy->GetNextEvent());
}