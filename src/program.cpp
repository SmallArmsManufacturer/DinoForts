#include "program.hpp"

#include <glm/gtc/type_ptr.hpp>
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

void Program::setAttribLocation(const char *name, GLuint location)
{
	use();

	GLint attrib = glGetAttribLocation(id, name);
	if (attrib == -1)
		cerr << "Warning: No attribute named '" << name << "' found." << endl;
	else
		glBindAttribLocation(id, location, name);
}

void Program::setUniformMatrix(const char *name, glm::mat3 &matrix)
{
	use();

	GLint uniform = glGetUniformLocation(id, name);
	if (uniform == -1)
		cerr << "Warning: No uniform named '" << name << "' found." << endl;
	else
		glUniformMatrix3fv(uniform, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Program::setUniformMatrix(const char *name, glm::mat4 &matrix)
{
	use();

	GLint uniform = glGetUniformLocation(id, name);
	if (uniform == -1)
		cerr << "Warning: No uniform named '" << name << "' found." << endl;
	else
		glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Program::setUniform(const char *name, GLint value)
{
	use();

	GLint uniform = glGetUniformLocation(id, name);
	if (uniform == -1)
		cerr << "Warning: No uniform named '" << name << "' found." << endl;
	else
		glUniform1i(uniform, value);
}
