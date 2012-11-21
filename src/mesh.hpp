#pragma once

#include "gl.hpp"

class Mesh
{
public:
	Mesh(const char *filename);
	~Mesh();
	void draw();

private:
	GLuint vao, vbo, ibo;
	int num_elements;
};