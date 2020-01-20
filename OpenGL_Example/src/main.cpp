// Vendor headers ********************************
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Global constants ********************************
const int windowWidth = 800;
const int windowHeight = 600;

int main()
{
	// Initialize GLFW
	glfwInit();
	// Set openGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Set openGL profile to core (ie modern)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window
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

	return 0;
}