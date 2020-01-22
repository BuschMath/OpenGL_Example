// Vendor headers ********************************
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
	// Set 2 triangle vertices
	// ************************************************
	// Set vertices of a triangle in normalized device coordinates
	float triangle0[] = {
		// Triangle 1
		// Lower left point
		-0.5f, -0.5f, 0.0f,
		// Lower right point
		0.5f, -0.5f, 0.0f,
		// Top point
		0.0f, 0.5f, 0.0f
	};

	float triangle1[] ={
		// Triangle 2
		// Top left point
		0.5f, 0.5f, 0.0f,
		// Top right point
		1.0f, 0.5f, 0.0f,
		// Bottom point
		1.0f, -0.5f, 0.0f
	};

	// ************************************************
	// Set rectangle indices
	// ************************************************
//	unsigned int indices[] = {
//		2, 1, 3,		// First triangle
//		1, 0, 3			// Second triangle
//	};

	// ************************************************
	// Vertex buffer object
	// ************************************************
	// Create a vertex buffer object to manage our vertex memory on the GPU
	unsigned int VBO[2];
	// Generate a unique ID for our vertex buffer
	glGenBuffers(2, VBO);

	// ************************************************
	// Element buffer object
	// ************************************************
//	unsigned int EBO;
//	glGenBuffers(1, &EBO);

	// ************************************************
	// Vertex array object
	// ************************************************
	// Create a vertex array object
	unsigned int VAO[2];
	// Give VAO an ID
	glGenVertexArrays(2, VAO);
	// Bind VAO
	glBindVertexArray(VAO[0]);

	// ************************************************
	// Bind data to VBO with active VAO and add vertex attributes
	// ************************************************
	// Bind our vertex buffer to set it as the active GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	// Copy our vertices to the vertex buffer's memory on the GPU
	// Last argument can be GL_STATIC_DRAW for rarely changing, GL_DYNAMIC_DRAW for frequent changing and
	// GL_STREAM_DRAW for changing every frame
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle0), triangle0, GL_STATIC_DRAW);

	// Set vertex attributes pointer and enable it
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Bind under VAO[1]
	glBindVertexArray(VAO[1]);
	// Bind our vertex buffer to set it as the active GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	// Copy our vertices to the vertex buffer's memory on the GPU
	// Last argument can be GL_STATIC_DRAW for rarely changing, GL_DYNAMIC_DRAW for frequent changing and
	// GL_STREAM_DRAW for changing every frame
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);

	// Set vertex attributes pointer and enable it
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ************************************************
	// Bind data to EBO with active VAO
	// ************************************************
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Deactivate VAO
	glBindVertexArray(0);

	// ************************************************
	// Vertex shader
	// ************************************************
	// Code for vertex shader
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	// Create shader object
	unsigned int vertexShader;
	// Assign a shader ID
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach shader code to shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile shader
	glCompileShader(vertexShader);

	// Check for shader compilation errors
	int success;
	char infoLog[512];
	// Checking compilation status
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// Get error log
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ************************************************
	// Fragment shader
	// ************************************************
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"\n"
		"void main()\n"
		"{\n"
		"\tFragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n";

	// Create shader object
	unsigned int fragmentShader;
	// Assign a shader ID
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach shader code to shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile shader
	glCompileShader(fragmentShader);

	// Check for shader compilation errors
	// Checking compilation status
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// Get error log
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// ************************************************
	// Shader program
	// ************************************************
	unsigned int shaderProgram;
	// Create ID for shader program
	shaderProgram = glCreateProgram();

	// Attach shaders
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Link shaders
	glLinkProgram(shaderProgram);

	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Activate shader program
	glUseProgram(shaderProgram);

	// Delete shader parts that are no longer in use
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

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

		glUseProgram(shaderProgram);
		// Triangle 0
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Triangle 1
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
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