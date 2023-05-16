#ifndef _ENGINE_WINDOW_H_
#define _ENGINE_WINDOW_H_

#include "IWindowingStrategy.h"
#include "Events/EventManager.h"
#include "Events/IListener.h"
#include "Events/Event.h"
#include "Windowing/X11/XWindowingStrategy.h"
#include <memory>
#include <exception>

class EngineWindow
{
public:
	void SetStrategy(IWindowingStrategy*);
	void Initialize(const unsigned int& x, const unsigned int& y, 
		const unsigned int& width, const unsigned int& height, 
		IWindowingStrategy::WindowType const& type = IWindowingStrategy::Desktop);
	void SwapBuffers();
	void CheckNextEvent();

public:
	EngineWindow();

protected:
	EventManager &m_EventManager;
	std::unique_ptr<IWindowingStrategy> m_WindowingStrategy;
};

#endif