#include "mesh.hpp"

#include <iostream>
#include <fstream>
#include <peng/mesh.hpp>

Mesh::Mesh(const char *filename)
{
	std::ifstream in(filename);
	Peng::Mesh mesh;
	in >> mesh;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Peng::Vertex), &mesh.vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Peng::Vertex), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Peng::Vertex), (GLvoid *) offsetof(Peng::Vertex, normal));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.triangles.size() * sizeof(Peng::Triangle), &mesh.triangles[0], GL_STATIC_DRAW);

	num_elements = mesh.triangles.size() * 3;
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void Mesh::draw()
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, num_elements, GL_UNSIGNED_INT, NULL);
}
