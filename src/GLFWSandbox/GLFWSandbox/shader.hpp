#ifndef SHADER_HPP
#define SHADER_HPP

#include "window.hpp"

unsigned int buildShader(const char *shaderName, int shaderType, const char *shaderSource, int *success) {

	// build shader
	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);

	// ensure shader compiled
	glGetShaderiv(shader, GL_COMPILE_STATUS, success);
	if(!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cerr << "Error: shader compile error on " << shaderName << "\n" << infoLog << std::endl;
		throw std::runtime_error("couldn't compile shader");
	}

	return shader;

}

/*class Shader {
	Shader(const char *shaderName, int shaderType, const char *shaderSource);

	~Shader();
};*/

#endif
