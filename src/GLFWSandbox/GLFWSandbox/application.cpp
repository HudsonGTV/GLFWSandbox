#include "application.hpp"

void onWindowResize(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

Application::Application() {

	if(!glfwInit()) {
		throw std::runtime_error("Couldn't init GLFW");
	}

	// Create an OpenGL window and set it as the active window
	window = std::make_unique<Window>(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Window");
	glfwMakeContextCurrent(window->get());
	glfwSetFramebufferSizeCallback(window->get(), onWindowResize);

	// Init GLAD (handles conversions between different GPU manufacturers)
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw std::runtime_error("Failed to initialize GLAD");
	}

	// Set the initial size of the renderable area
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

}

Application::~Application() {
	window.reset();
	glfwTerminate();
}

void Application::loop() {
	while(!glfwWindowShouldClose(window->get())) {
		glfwSwapBuffers(window->get());
		glfwPollEvents();
	}
}
