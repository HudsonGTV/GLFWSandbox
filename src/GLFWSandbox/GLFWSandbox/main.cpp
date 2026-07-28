#include <iostream>
#include <glad/glad.h>

#include "window.hpp"
#include "config.hpp"

int main() {

	// Init GLAD (handles conversions between different GPU manufacturers)
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw std::runtime_error("Failed to initialize GLAD");

	Window window{WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Window"};
	glfwMakeContextCurrent(window.get());

	while(1);

	return 0;

}
