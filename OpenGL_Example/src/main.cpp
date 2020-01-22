// Vendor headers ********************************
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Local headers ********************************
#include "Shader.h"

// Global constants ********************************
const int windowWidth = 800;
const int windowHeight = 600;

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
	// Set rectangle vertices
	// ************************************************
	// Set vertices of a triangle in normalized device coordinates
	float vertices[] = {
		// Lower left point		// Colors
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,
		// Lower right point
		0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
		// Top right point
		0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f,
		// Top left point
		-0.5f, 0.5f, 0.0f,		0.0f, 0.0f, 0.0f
	};

	// ************************************************
	// Set rectangle indices
	// ************************************************
	unsigned int indices[] = {
		2, 1, 3,		// First triangle
		1, 0, 3			// Second triangle
	};

	// ************************************************
	// Vertex buffer object
	// ************************************************
	// Create a vertex buffer object to manage our vertex memory on the GPU
	unsigned int VBO;
	// Generate a unique ID for our vertex buffer
	glGenBuffers(1, &VBO);

	// ************************************************
	// Element buffer object
	// ************************************************
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	// ************************************************
	// Vertex array object
	// ************************************************
	// Create a vertex array object
	unsigned int VAO;
	// Give VAO an ID
	glGenVertexArrays(1, &VAO);
	// Bind VAO
	glBindVertexArray(VAO);

	// ************************************************
	// Bind data to VBO with active VAO and add vertex attributes
	// ************************************************
	// Bind our vertex buffer to set it as the active GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Copy our vertices to the vertex buffer's memory on the GPU
	// Last argument can be GL_STATIC_DRAW for rarely changing, GL_DYNAMIC_DRAW for frequent changing and
	// GL_STREAM_DRAW for changing every frame
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Set vertex attributes pointer and enable it
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// ************************************************
	// Bind data to EBO with active VAO
	// ************************************************
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Deactivate VAO
	glBindVertexArray(0);

	// ************************************************
	// Shader program
	// ************************************************
	Shader shader("vertexShader.shader", "fragmentShader.shader");

	// Activate shader program
	shader.Use();

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
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

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