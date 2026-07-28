/**
* Wrapper for the GLFWwindow to make it more memory-safe
**/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>

class Window {

private:
	GLFWwindow* window {nullptr};

public:
	explicit Window(int width, int height, const char *title);
	~Window();

	// disable copy constructor
	Window(Window& other) = delete;

	// disable letting another pointer have this
	Window& operator=(const Window& other) = delete;

	// allow moving
	Window(Window&& other) noexcept;

	GLFWwindow* get();

};

#endif