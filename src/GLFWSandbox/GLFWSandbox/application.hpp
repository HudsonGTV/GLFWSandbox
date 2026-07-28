#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <memory>

#include "window.hpp"
#include "config.hpp"

class Application {

private:
	std::unique_ptr<Window> window;

public:
	Application();
	~Application();

	void loop();

};

#endif
