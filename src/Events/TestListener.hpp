#ifndef _TEST_LISTENER_HPP_
#define _TEST_LISTENER_HPP_

#include "IListener.h"
#include <iostream>

class TestListener : public IListener
{
	virtual void OnUpdate(Event& event) override
	{
		std::vector<int> data = *std::static_pointer_cast< std::vector<int> >(event.GetParamters());
		std::cout << "From Listener:" << data.at(0) << " " << data.at(1) << std::endl;
	}
};

#endif