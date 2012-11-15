#include "program.hpp"

#include <iostream>

using namespace std;

Program::Program(vector<ShaderPtr> &shaders) throw(ProgramLinkException)
{
	id = glCreateProgram();
	this->shaders = shaders;

	// Attach the shaders
	for (ShaderPtr shader : shaders)
	{
		glAttachShader(id, shader->id);
	}

	// Link the program
	glLinkProgram(id);

	// Check if linking was successful
	GLint status;
	glGetProgramiv(id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		// Write the error to stderr
		GLsizei length;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
		char *log = new char[length];
		glGetProgramInfoLog(id, length, NULL, log);
		cerr << "Error: Unable to link shader program" << endl;
		cerr << log << endl;
		delete log;

		glDeleteProgram(id);
		throw ProgramLinkException();
	}
}

Program::~Program()
{
	// Detach the shaders
	for (ShaderPtr shader : shaders)
		glDetachShader(id, shader->id);

	glDeleteProgram(id);
}

void Program::use()
{
	glUseProgram(id);
}

GLuint Program::getAttribLocation(const char *name)
{
	use();

	GLint attrib = glGetAttribLocation(id, name);
	if (attrib == -1)
		cerr << "Warning: No attribute named '" << name << "' found." << endl;
	
	return attrib;
}
