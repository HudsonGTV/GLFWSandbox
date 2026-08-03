/**
* Main application object
**/

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <memory>

#include "config.hpp"
#include "window.hpp"
#include "input.hpp"
#include "shader.hpp"

class Application {

private:
	std::unique_ptr<Window> window;

public:
	Application();
	~Application();

	void loop();

};

#endif
