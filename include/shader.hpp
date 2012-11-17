#pragma once

#include <memory>
#include <stdexcept>
#include "gl.hpp"

class ShaderCompilationException : public std::exception {};

class Shader
{
	friend class Program;

public:
	Shader(const char *filename, GLuint type) throw(ShaderCompilationException);
	~Shader();

private:
	Shader(const Shader &);
    const Shader &operator=(const Shader &);

	GLuint id;
};

typedef std::shared_ptr<Shader> ShaderPtr;
typedef std::weak_ptr<Shader> ShaderWeakPtr;
