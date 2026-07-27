#include <iostream>
#include <glad/glad.h>

#include "window.hpp"
#include "config.hpp"

int main() {

	Window window{WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Window"};
	glfwMakeContextCurrent(window.get());

	while(1);

	return 0;

}
