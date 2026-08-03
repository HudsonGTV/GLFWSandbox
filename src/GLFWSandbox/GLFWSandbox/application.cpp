#include "application.hpp"

void onWindowResize(GLFWwindow *window, int width, int height) {
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



/**
* TODO: Wrap shader stuff in an object to handle deletion of shader objects automatically
**/
unsigned int makeTriangle() {

	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	int success = 1;

	// build vertex shader
	unsigned int vertexShader = buildShader("vertex shader", GL_VERTEX_SHADER, vertexShaderSource, &success);
	// build fragment shader
	unsigned int fragmentShader = buildShader("fragment shader", GL_FRAGMENT_SHADER, fragmentShaderSource, &success);

	// link shaders
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "Error: Shader linking failed\n" << infoLog << std::endl;
		throw std::runtime_error("Shader linking failed");
	}

	// clean up shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;

}

void drawTriangle(unsigned int shaderProgram, unsigned int *VAO) {
	glUseProgram(shaderProgram);
	glBindVertexArray(*VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Application::loop() {

	//TODO: break this up into functions/objects
	unsigned int shaderProgram = makeTriangle();

	// vertex data
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	// vertex buff obj & vertex array obj
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	while(!glfwWindowShouldClose(window->get())) {

		handleInput(window->get());

		// render stuff here
		glClearColor(0.5f, 0.25f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		drawTriangle(shaderProgram, &VAO);

		glfwSwapBuffers(window->get());
		glfwPollEvents();

	}

}
