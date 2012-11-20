#include <cstdlib>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "gl.hpp"
#include "program.hpp"
#include "shader.hpp"

using namespace std;

int main(int argc, const char *argv[])
{
	// Initialise GLFW
	if (!glfwInit()) return EXIT_FAILURE;

	// Ask for a forward-compatible OpenGL 3.2 Core context
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
	glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the main window
	if (!glfwOpenWindow(800, 600, 0, 0, 0, 0, 0, 0, GLFW_WINDOW))
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	// Set the main window title
	glfwSetWindowTitle("Dino Forts");
	
	// Initialise GLEW
	#ifdef __MINGW32__
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK) {
			cerr << "Unable to initialize GLEW: " << glewGetErrorString(err) << endl;
			return EXIT_FAILURE;
		}
		cout << "Using GLEW " << glewGetString(GLEW_VERSION) << endl;
	#endif

	// Load and compile the shaders
	ShaderPtr vertex_shader(new Shader("assets/shaders/test.vs", GL_VERTEX_SHADER));
	ShaderPtr fragment_shader(new Shader("assets/shaders/test.fs", GL_FRAGMENT_SHADER));

	// Link the shader program
	vector<ShaderPtr> shaders;
	shaders.push_back(vertex_shader);
	shaders.push_back(fragment_shader);
	Program program(shaders);

	// Set up the triangle vertex array
	GLuint vao, vbo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	GLfloat vertices[] = {  0,  1,  0,   // Vertex 1 position
	                        0,  0,  -1,   // Vertex 1 normal
	                        1, -1,  0,   // Vertex 2 position
	                        0,  0,  -1,   // Vertex 2 normal
	                       -1, -1,  0,   // Vertex 3 position
	                        0,  0,  -1 }; // Vertex 3 normal
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(program.getAttribLocation("in_Position"), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(program.getAttribLocation("in_Position"));
	glVertexAttribPointer(program.getAttribLocation("in_Normal"), 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(program.getAttribLocation("in_Normal"));

	// Set up the modelview and projection matrices
	glm::mat4 projection = glm::perspective(45.0f, 800.0f / 600.0f, 1.0f, 100.0f);
	glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
	modelview = glm::rotate(modelview, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat3 normalmatrix = glm::transpose(glm::inverse(glm::mat3(modelview)));
	program.setUniformMatrix("projection", projection);
	program.setUniformMatrix("modelview", modelview);
	program.setUniformMatrix("normalmatrix", normalmatrix);

	// Enter main event loop
	int running = GL_TRUE;
	while(running)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glFlush();
		glfwSwapBuffers();
		running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
	}

	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	glfwTerminate();

	return EXIT_SUCCESS;
}
