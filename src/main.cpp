#include <cstdlib>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "gl.hpp"
#include "mesh.hpp"
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
	if (!glfwOpenWindow(800, 600, 8, 8, 8, 8, 24, 8, GLFW_WINDOW))
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
	ShaderPtr passthrough_vertex_shader(new Shader("assets/shaders/passthrough.vs", GL_VERTEX_SHADER));
	ShaderPtr ssao_fragment_shader(new Shader("assets/shaders/ssao.fs", GL_FRAGMENT_SHADER));

	// Link the shader program
	vector<ShaderPtr> shaders;
	shaders.push_back(vertex_shader);
	shaders.push_back(fragment_shader);
	Program program(shaders);

	// Link the SSAO shader program
	vector<ShaderPtr> ssao_shaders;
	ssao_shaders.push_back(passthrough_vertex_shader);
	ssao_shaders.push_back(ssao_fragment_shader);
	Program ssao_program(ssao_shaders);

	// Set up the attribute indices
	program.setAttribLocation("in_Position", 0);
	program.setAttribLocation("in_Normal", 1);
	ssao_program.setAttribLocation("in_Position", 0);

	// Set up the triangle vertex array
	Mesh mesh("test.peng");

	// Set up the modelview and projection matrices
	glm::mat4 projection = glm::perspective(45.0f, 800.0f / 600.0f, 1.0f, 100.0f);
	glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
	glm::mat3 normalmatrix;
	program.setUniformMatrix("projection", projection);

	// Enable backface culling and depth testing
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	/*// Create the FBO
	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// Create the texture that the colour data will be rendered to in the first pass
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	GLenum buf = GL_COLOR_ATTACHMENT0;
	glDrawBuffers(1, &buf);

	// Create the depth buffer that will be rendered to in the first pass
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 800, 600);

	// Attach the depth buffer and the texture to the FBO
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, tex, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);*/

GLuint fbo_depth, fbo_texture, fbo;
	glGenRenderbuffers(1, &fbo_depth); // Generate one render buffer and store the ID in fbo_depth  
glBindRenderbuffer(GL_RENDERBUFFER, fbo_depth); // Bind the fbo_depth render buffer  
  
glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 800, 600); // Set the render buffer storage to be a depth component, with a width and height of the window  
  
glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbo_depth); // Set the render buffer of this buffer to the depth buffer  
  
glBindRenderbuffer(GL_RENDERBUFFER, 0); // Unbind the render buffer  
glGenTextures(1, &fbo_texture); // Generate one texture  
glBindTexture(GL_TEXTURE_2D, fbo_texture); // Bind the texture fbo_texture  
  
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); // Create a standard texture with the width and height of our window  
  
// Setup the basic texture parameters  
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
  
// Unbind the texture  
glBindTexture(GL_TEXTURE_2D, 0);  
glGenFramebuffers(1, &fbo); // Generate one frame buffer and store the ID in fbo  
glBindFramebuffer(GL_FRAMEBUFFER, fbo); // Bind our frame buffer  
  
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture, 0); // Attach the texture fbo_texture to the color buffer in our frame buffer  
  
glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbo_depth); // Attach the depth buffer fbo_depth to our frame buffer  
  
GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER); // Check that status of our generated frame buffer  
  
if (status != GL_FRAMEBUFFER_COMPLETE) // If the frame buffer does not report back as complete  
{  
std::cout << "Couldn't create frame buffer" << std::endl; // Output an error to the console  
exit(0); // Exit the application  
}  
  
glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind our frame buffer  


	// Set up the quad for ssao
	GLuint vao, vbo, ibo;
	GLfloat vertices[] = { -1.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0, -1.0, 0.0, -1.0, -1.0, 0.0 };
	GLubyte indices[] = { 3, 1, 0, 3, 2, 1 };
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set up sampler
	ssao_program.setUniform("s", 0);

	// Enter main event loop
	int running = GL_TRUE;
	double prevTime = glfwGetTime();
	while(running)
	{
		double dt = glfwGetTime() - prevTime;
		prevTime += dt;

		// Rotate the modelview matrix and update the normal matrix accordingly
		modelview = glm::rotate(modelview, 30 * (float) dt, glm::vec3(0.5f, 1.0f, 0.0f));
		normalmatrix = glm::transpose(glm::inverse(glm::mat3(modelview)));
		program.setUniformMatrix("modelview", modelview);
		program.setUniformMatrix("normalmatrix", normalmatrix);

		// Draw to the temporary FBO
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);
		program.use();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mesh.draw();

		// Switch to the main FBO
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, fbo_texture);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		ssao_program.use();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);

		glFlush();
		glfwSwapBuffers();
		running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
