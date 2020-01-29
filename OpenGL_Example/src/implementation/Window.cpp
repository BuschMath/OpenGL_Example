#include "Window.h"

#include <iostream>

// Deals with window resizing, updating the rendering window
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

Window::Window()
{
	window = nullptr;
	windowWidth = 0;
	windowHeight = 0;
}

Window::Window(int windowWidth_, int windowHeight_, std::string windowTitle)
{
	windowWidth = windowWidth_;
	windowHeight = windowHeight_;

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
	window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
	// If window creation fails, display error and safely exit
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
	}
	// Make window the current context
	glfwMakeContextCurrent(window);

	// ************************************************
	// Initialize GLAD
	// ************************************************
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	// ************************************************
	// Set viewport
	// ************************************************
	// Set the size of the rendering window
	// This maps the openGL render space from -1 to 1 over to 0 to windowWidth and same for height
	glViewport(0, 0, windowWidth, windowHeight);

	// Register window resize helper function with glfw
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

Window::~Window()
{
}

GLFWwindow* Window::GetWindow()
{
	return window;
}

void Window::SetInputMode(InputModeType mode, InputValueType value)
{
	if (mode == InputModeType::CURSOR)
	{
		if (value == InputValueType::NORMAL)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else if (value == InputValueType::HIDDEN)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		else if (value == InputValueType::DISABLED)
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			std::cout << "ERROR::WINDOW::SETINPUTMODE::VALUEERROR\n";
	}
	else if (mode == InputModeType::LOCK_KEY_MODS)
	{
		if (value == InputValueType::TRUE)
			glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);
		else if (value == InputValueType::FALSE)
			glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_FALSE);
		else
		{
			std::cout << "ERROR::WINDOW::SETINPUTMODE::VALUEERROR\n";
		}
	}
	else if (mode == InputModeType::RAW_MOUSE_MOTION)
	{
		if (value == InputValueType::TRUE)
			glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		else if (value == InputValueType::FALSE)
			glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
		else
		{
			std::cout << "ERROR::WINDOW::SETINPUTMODE::VALUEERROR\n";
		}
	}
	else if (mode == InputModeType::STICKY_KEYS)
	{
		if (value == InputValueType::TRUE)
			glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
		else if (value == InputValueType::FALSE)
			glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);
		else
		{
			std::cout << "ERROR::WINDOW::SETINPUTMODE::VALUEERROR\n";
		}
	}
	else if (mode == InputModeType::STICKY_MOUSE)
	{
		if (value == InputValueType::TRUE)
			glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);
		else if (value == InputValueType::FALSE)
			glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, GLFW_FALSE);
		else
		{
			std::cout << "ERROR::WINDOW::SETINPUTMODE::VALUEERROR\n";
		}
	}
	else
		std::cout << "ERROR::WINDOW::SETINPUTMODE::MODEERROR\n";
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}