#include "shader.hpp"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Shader::Shader(const char *filename, GLuint type) throw(ShaderCompilationException)
{
	// Load the shader source
	ifstream stream(filename);
	if (!stream.is_open()) throw ShaderCompilationException();
	string source((istreambuf_iterator<char>(stream)), (istreambuf_iterator<char>()));
	const char *c_str = source.c_str();

	// Compile the shader
	id = glCreateShader(type);
	glShaderSource(id, 1, &c_str, NULL);
	glCompileShader(id);

	// Check if compilation was successful
	GLint status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		// Write the error to stderr
		GLsizei length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *log = new char[length];
		glGetShaderInfoLog(id, length, NULL, log);
		cerr << "Error: Unable to compile shader " << filename << endl;
		cerr << log << endl;
		delete log;

		glDeleteShader(id);
		throw ShaderCompilationException();
	}
}

Shader::~Shader()
{
	glDeleteShader(id);
}
