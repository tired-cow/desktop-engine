#include "EngineWindow.h"

EngineWindow::EngineWindow( ) 
	: m_EventManager{EventManager::GetInstance()}
{
	m_WindowingStrategy = std::make_unique<XWindowingStrategy>();
	m_EventManager.RegisterEvent("MouseMoved");
	// m_EventManager.RegisterEvent("Expose");
	m_EventManager.RegisterEvent("KeyPressed");
}

void EngineWindow::SetStrategy( IWindowingStrategy *strategy )
{
	if (strategy == nullptr)
		throw "Strategy cannot be null!";
	
	if (m_WindowingStrategy != nullptr)
		m_WindowingStrategy.release( );

	m_WindowingStrategy = std::unique_ptr<IWindowingStrategy>( strategy );
}

void EngineWindow::Initialize(const unsigned int& x, const unsigned int& y, 
		const unsigned int& width, const unsigned int& height, 
		IWindowingStrategy::WindowType const& type)
{
	m_WindowingStrategy->CreateWindow(x, y, width, height, type);
}

void EngineWindow::SwapBuffers()
{
	m_WindowingStrategy->SwapBuffers();
}

void EngineWindow::CheckNextEvent()
{
	Event event = m_WindowingStrategy->GetNextEvent();
	if (event.GetParamters() != nullptr)
		m_EventManager.NotifyListeners(event);
}