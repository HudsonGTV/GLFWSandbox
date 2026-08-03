/**
* Wrapper for the GLFWwindow to make it more memory-safe
**/

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {


private:
	GLFWwindow *window{nullptr};

public:
	explicit Window(int width, int height, const char *title);
	~Window();

	// disable copy constructor
	Window(const Window &other) = delete;
	// disable letting another pointer have this
	Window &operator=(const Window &other) = delete;
	// allow moving to new var
	Window(Window &&other) noexcept;
	// allow moving to existing var (where other is already initialized)
	Window &operator=(Window &&other) noexcept;


	GLFWwindow *get() const;

};

#endif