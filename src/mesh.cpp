#include "mesh.hpp"

Mesh::Mesh()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	GLfloat vertices[] = {  -1,  1, -1,   // Vertex 0 position
	                        -1,  1, -1,   // Vertex 0 normal
	                        -1,  1,  1,   // Vertex 1 position
	                        -1,  1,  1,   // Vertex 1 normal
	                         1,  1,  1,   // Vertex 2 position
	                         1,  1,  1,   // Vertex 2 normal
	                         1,  1, -1,   // Vertex 3 position
	                         1,  1, -1,   // Vertex 3 normal
	                        -1, -1, -1,   // Vertex 4 position
	                        -1, -1, -1,   // Vertex 4 normal
	                        -1, -1,  1,   // Vertex 5 position
	                        -1, -1,  1,   // Vertex 5 normal
	                         1, -1,  1,   // Vertex 6 position
	                         1, -1,  1,   // Vertex 6 normal
	                         1, -1, -1,   // Vertex 7 position
	                         1, -1, -1 }; // Vertex 7 normal
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	GLubyte indices[] = { 0, 1, 2, // Top
	                      0, 2, 3,
	                      4, 6, 5, // Bottom
	                      4, 7, 6,
	                      4, 0, 3, // Back
	                      4, 3, 7,
	                      5, 2, 1, // Front
	                      5, 6, 2,
	                      0, 5, 1, // Left
	                      0, 4, 5,
	                      7, 3, 2, // Right
	                      7, 2, 6 };
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, NULL);
}
