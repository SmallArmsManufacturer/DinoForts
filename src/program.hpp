#pragma once

#include <memory>
#include <stdexcept>
#include <vector>
#include "gl.hpp"
#include "maths.hpp"
#include "shader.hpp"

class ProgramLinkException : public std::exception {};

class Program
{
public:
	Program(std::vector<ShaderPtr> &shaders) throw(ProgramLinkException);
	~Program();
	void use();
	GLuint getAttribLocation(const char *name);
	void setUniformMatrix(const char *name, Maths::Matrix &matrix);

private:
	Program(const Program &);
    const Program &operator=(const Program &);
    
	GLuint id;
	std::vector<ShaderPtr> shaders;
};

typedef std::shared_ptr<Program> ProgramPtr;
typedef std::weak_ptr<Program> ProgramWeakPtr;
