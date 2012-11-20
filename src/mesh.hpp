#pragma once

#include "gl.hpp"

class Mesh
{
public:
	Mesh();
	~Mesh();
	void draw();

private:
	GLuint vao, vbo, ibo;
};