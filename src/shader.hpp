#pragma once

#include <stdexcept>
#include <tr1/memory>
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

typedef std::tr1::shared_ptr<Shader> ShaderPtr;
typedef std::tr1::weak_ptr<Shader> ShaderWeakPtr;
