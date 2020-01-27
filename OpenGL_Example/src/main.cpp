// Vendor headers ********************************
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb_image.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

// Local headers ********************************
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "VertexAttribute.h"
#include "Texture.h"

// Global constants ********************************
const int windowWidth = 800;
const int windowHeight = 600;
const int numberOfVertices = 24;
const int numberOfDataPerVertex = 5;
const int numberOfData = numberOfVertices * numberOfDataPerVertex;

// Helper function prototypes ********************************
// Deals with window resizing, updating the rendering window
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

int main()
{
	// ************************************************
	// Initialize GLFW
	// ************************************************
	glfwInit();
	// Set openGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Set openGL profile to core (ie modern)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ************************************************
	// Create a window
	// ************************************************
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Test Window Title", NULL, NULL);
	// If window creation fails, display error and safely exit
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Make window the current context
	glfwMakeContextCurrent(window);

	// ************************************************
	// Initialize GLAD
	// ************************************************
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// ************************************************
	// Set viewport
	// ************************************************
	// Set the size of the rendering window
	// This maps the openGL render space from -1 to 1 over to 0 to windowWidth and same for height
	glViewport(0, 0, windowWidth, windowHeight);

	// Register window resize helper function with glfw
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// ************************************************
	// Load and generate texture
	// ************************************************
	Texture texture0("res/container.jpg", ImageType::JPG, WrapType::REPEAT, FilterType::LINEAR);
	Texture texture1("res/awesomeface.png", ImageType::PNG, WrapType::REPEAT, FilterType::LINEAR);

	// ************************************************
	// Set rectangle vertices
	// ************************************************
	// Set vertices of a triangle in normalized device coordinates
	float vertices[] = {
		// Vertices				// Texture		// Ver
		// Back face
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,		// 0
		 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,		// 1
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		// 2
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		// 3
		// Front face
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		// 4
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,		// 5
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,		// 6
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,		// 7
		// Left face
		-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		// 8
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		// 9
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		// 10
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		// 11
		// Right face
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		// 12
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		// 13
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		// 14
		 0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		// 15
		 // Bottom face
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,		// 16
		 0.5f, -0.5f, -0.5f,	1.0f, 1.0f,		// 17
		 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,		// 18
		-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,		// 19
		// Top face
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,		// 20
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,		// 21
		 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,		// 22
		-0.5f,  0.5f,  0.5f,	0.0f, 0.0f 		// 23
	};

	// ************************************************
	// Set rectangle indices
	// ************************************************
	unsigned int indices[] = {
		// Back face
		0, 1, 2,			// First triangle
		2, 3, 0,			// Second triangle
		// Front face
		4, 5, 6,			// First triangle
		6, 7, 4,			// Second triangle
		// Left face
		8, 9, 10,			// First triangle
		10, 11, 8,			// Second triangle
		// Right face
		12, 13, 14,			// First triangle
		14, 15, 12,			// Second triangle
		// Bottom face
		16, 17, 18,			// First triangle
		18, 19, 16,			// Second triangle
		// Top face
		20, 21, 22,			// First triangle
		22, 23, 20			// Second triangle
	};

	// ************************************************
	// Vertex buffer object
	// ************************************************
	// Create a vertex buffer object to manage our vertex memory on the GPU
	VertexBuffer VBO;

	// ************************************************
	// Vertex array object
	// ************************************************
	// Create a vertex array object
	VertexArray VAO;
	VAO.Bind();

	// ************************************************
	// Bind data to VBO with active VAO and add vertex attributes
	// ************************************************
	// Copy our vertices to the vertex buffer's memory on the GPU
	// Last argument can be STATIC for rarely changing, DYNAMIC for frequent changing and STREAM for 
	//changing every frame
	VBO.SetVertices(vertices, numberOfData, DrawType::STATIC);
	// Reactivate vertex buffer after SetVertices
	VBO.Bind();

	// Set vertex attributes
	VertexAttribute VA0, VA1;
	VA0.SetID(0);
	VA0.SetSize(3);
	VA0.SetOffset(0);
	VAO.AddVertexAttribute(VA0);

	VA1.SetID(1);
	VA1.SetSize(2);
	VA1.SetOffset(3);
	VAO.AddVertexAttribute(VA1);

	// Set indices
	VAO.SetIndices(indices, 36, DrawType::STATIC);
	VAO.SetVertexStride(numberOfDataPerVertex);
	VAO.SetVAO_EBO();
	
	VAO.Unbind();

	// ************************************************
	// Shader program
	// ************************************************
	Shader shader("vertexShader.shader", "fragmentShader.shader");

	// Activate shader program
	shader.Use();

	// Set uniforms
	shader.SetInt("texture0", 0);
	shader.SetInt("texture1", 1);

	// ************************************************
	// Create Model View Projection matrix
	// ************************************************
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), float(windowWidth) / windowHeight, 0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);

	// ************************************************
	// Render loop
	// ************************************************
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// Rendering
		// Set clear color state defined as Red, Blue, Green, Alpha
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		// Color the buffer to match clear color state
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();

		// ************************************************
		// Send MVP matrix uniforms
		// ************************************************
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		int modelLoc = glGetUniformLocation(shader.GetID(), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int viewLoc = glGetUniformLocation(shader.GetID(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projectionLoc = glGetUniformLocation(shader.GetID(), "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0.GetID());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1.GetID());
		VAO.Bind();
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		VAO.Unbind();

		// Load image buffer to display
		glfwSwapBuffers(window);
		// Check to see if any events have occured and deal with them
		glfwPollEvents();
	}

	// Clean-up GLFW
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}