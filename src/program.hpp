#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <stdexcept>
#include <vector>
#include "gl.hpp"
#include "shader.hpp"

class ProgramLinkException : public std::exception {};

class Program
{
public:
	Program(std::vector<ShaderPtr> &shaders) throw(ProgramLinkException);
	~Program();
	void use();
	void setAttribLocation(const char *name, GLuint location);
	void setUniformMatrix(const char *name, glm::mat3 &matrix);
	void setUniformMatrix(const char *name, glm::mat4 &matrix);
	void setUniform(const char *name, GLint value);

private:
	Program(const Program &);
    const Program &operator=(const Program &);
    
	GLuint id;
	std::vector<ShaderPtr> shaders;
};

typedef std::shared_ptr<Program> ProgramPtr;
typedef std::weak_ptr<Program> ProgramWeakPtr;
