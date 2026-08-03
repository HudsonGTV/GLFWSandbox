#include "window.hpp"

Window::Window(int width, int height, const char *title) {

	// Configure GLFW
	// Note: See https://www.glfw.org/docs/latest/window.html#window_hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Generate a window
	this->window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if(!this->window) {
		throw std::runtime_error("Failed to create window");
	}

}

Window::~Window() {
	glfwDestroyWindow(this->window);
}

Window::Window(Window &&other) noexcept : window(other.window) {
	other.window = nullptr;
}

Window &Window::operator=(Window &&other) noexcept {
	if(this != &other) {
		if(this->window) {
			glfwDestroyWindow(this->window);
		}
		this->window = other.window;
		other.window = nullptr;
	}
	return *this;
}

GLFWwindow *Window::get() const {
	return this->window;
}

